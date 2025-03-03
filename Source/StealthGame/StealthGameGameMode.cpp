// Copyright Epic Games, Inc. All Rights Reserved.

#include "StealthGameGameMode.h"
#include "StealthGameCharacter.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AStealthGameGameMode::AStealthGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AStealthGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Bind to player death
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerCharacter);
	Player->OnPlayerDeath.AddUniqueDynamic(this, &AStealthGameGameMode::ReloadLevel);

	//Bind to player winning
	//Get the goal first.
	AActor* GoalActor = UGameplayStatics::GetActorOfClass(GetWorld(), AGoal::StaticClass());
	Goal = Cast<AGoal>(GoalActor);
	//Bind
	Goal->OnGameWon.AddUniqueDynamic(this, &AStealthGameGameMode::ReloadLevel);
}

void AStealthGameGameMode::ReloadLevel()
{
	FTimerHandle TimerHandle;

	FTimerDynamicDelegate TimerDelegate;
	TimerDelegate.BindDynamic(this, &AStealthGameGameMode::Handle_TimerEnded);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 5, false);
}

void AStealthGameGameMode::Handle_TimerEnded()
{
	FString LevelString = UGameplayStatics::GetCurrentLevelName(GetWorld());
	FName LevelName = FName(LevelString);
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}