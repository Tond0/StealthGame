// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AI/EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "InputActionValue.h"
#include "Components/SkeletalMeshComponent.h"
#include "StealthGame/StealthGameGameMode.h"

#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	AttackCheckLocation = CreateDefaultSubobject<USceneComponent>("AttackCheckPos");
	AttackCheckLocation->SetupAttachment(RootComponent);
}

void APlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	AStealthGameGameMode* StealthGameMode = Cast<AStealthGameGameMode>(GameModeBase);
	StealthGameMode->SetPlayer(this);
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{

		// Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Crouch);

		// Attacking
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::TryAttack);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Crouch(const FInputActionValue& Value)
{
	if (CanCrouch())
		Super::Crouch();
	else
		UnCrouch();
}

void APlayerCharacter::TryAttack(const FInputActionValue& Value)
{
	//Cant attack if its falling.
	if (GetCharacterMovement()->IsFalling()) return;

	FHitResult OutHit;

	FVector TraceLocationStart = AttackCheckLocation->GetComponentLocation();
	FVector TraceLocationEnd = TraceLocationStart + GetActorForwardVector() * AttackCheckLenght;

	FCollisionObjectQueryParams ObjParams;
	ObjParams.AddObjectTypesToQuery(ECC_GameTraceChannel1);

	FCollisionQueryParams TraceParams;

	if (!GetWorld()->LineTraceSingleByObjectType(OutHit, TraceLocationStart, TraceLocationEnd, ObjParams, TraceParams))
	{
		DrawDebugLine(GetWorld(), TraceLocationStart, TraceLocationEnd, FColor::Red, true, 5, 0, 5);
		return;
	}

	DrawDebugLine(GetWorld(), TraceLocationStart, TraceLocationEnd, FColor::Green, true, 5, 0, 5);

	AActor* HitActor = OutHit.GetActor();
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(HitActor);
	const UBlackboardComponent* EnemyBlackBoard = Enemy->GetBlackBoardComponent();

	//If enemy can't be stealth attack we just return.
	if(!Enemy->CanBeAttacked()) return;
	Enemy->ReceiveAttack();

	//Fix animation if its crouched.
	/*if (bIsCrouched)
	{
		USkeletalMeshComponent* SkeletalMesh = GetMesh();
		FVector RelativeLocation = SkeletalMesh->GetRelativeLocation();
		RelativeLocation.Z = -90;
		SkeletalMesh->SetRelativeLocation(RelativeLocation);
	}*/

	UnCrouch();
	//Disable collision for animation.
	SetActorEnableCollision(false);
	//FIXME: Se ho tempo queste cose qua sotto dovrebbero stare in un'altra funzione per alleggerire TryAttack. Se non ho tempo m'attacco.
	//Set Player Transform for the animation
	FTransform BehindEnemyTransform;
	GetBehindEnemyTransform(BehindEnemyTransform, Enemy);
	SetActorTransform(BehindEnemyTransform);
	
	//SetUp The Attack!
	IsAttacking = true;
	
	//Disable All Inputs
	DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void APlayerCharacter::GetBehindEnemyTransform(FTransform& BehindTransform, AEnemyCharacter* Enemy)
{
	//Get Enemy Tranform
	FTransform EnemyTransform = Enemy->GetActorTransform();

	//Location
	FVector BehindPlayerLocation;
	FVector EnemyLocation = EnemyTransform.GetLocation();
	FVector EnemyForward = Enemy->GetActorForwardVector();
	//165 is the offset for the animation.
	BehindPlayerLocation = (EnemyForward * -165) + EnemyLocation;
	BehindTransform.SetLocation(BehindPlayerLocation);

	//Rotation
	FQuat EnemyRotator = EnemyTransform.GetRotation();
	BehindTransform.SetRotation(EnemyRotator);
}

void APlayerCharacter::ReceiveAttack()
{
	OnPlayerDeath.Execute();
	
	//FIXME: Ci sono MILIONI di modi per farlo meglio, ma essendo stato malato 1 settimana e l'altra sono stato a rotterdam, m'attacco.
	// Si, sto cercando di giustificarmi.
	//Player become invisible cause destroying can create problems.
	GetMesh()->SetVisibility(false);
	//Destroy();
}