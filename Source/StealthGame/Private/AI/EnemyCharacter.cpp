// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyCharacter.h"
#include "AI/AIBehaviourComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIBehaviourComponent = CreateDefaultSubobject<UAIBehaviourComponent>("AI Behaviour");
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	BlackBoardComponent = UAIBlueprintHelperLibrary::GetBlackboard(this);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::Attack(AStealthGameCharacter* CharacterToAttack)
{
	IsAttacking = true;

	CharacterToAttack->ReceiveAttack();
}

void AEnemyCharacter::ReceiveAttack()
{
	//Update Bool Blackboard.
	BlackBoardComponent->SetValueAsBool("IsBeingAttacked", true);
	//Disable Collision.
	SetActorEnableCollision(false);
}

bool AEnemyCharacter::CanBeAttacked()
{
	FName PlayerBlackboardKey = "Player";
	FName StimulusLocationBlackboardKey = "StimulusLocation";

	//If the enemy doesnt even suspect that the player is around, we can kill him 100%
	UObject* Player = BlackBoardComponent->GetValueAsObject(PlayerBlackboardKey);
	if (!IsValid(Player)) return true;

	//If the enemy knows the player is around we check if its investigating or its a direct contact.
	bool IsInvestigating = BlackBoardComponent->IsVectorValueSet(StimulusLocationBlackboardKey);
	if (IsInvestigating) return true;

	return false;
}

