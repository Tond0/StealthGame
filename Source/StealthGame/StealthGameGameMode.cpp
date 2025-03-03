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

void AStealthGameGameMode::SetGoal(AGoal* NewGoal)
{
	//Bind
	NewGoal->OnGoalReached.BindDynamic(this, &AStealthGameGameMode::Handle_GameWon);
}

void AStealthGameGameMode::SetPlayer(APlayerCharacter* NewPlayerCharacter)
{
	//Bind
	NewPlayerCharacter->OnPlayerDeath.BindDynamic(this, &AStealthGameGameMode::Handle_GameLost);
}

void AStealthGameGameMode::Handle_GameWon()
{
	OnGameOver.Broadcast(true);
	ReloadLevel();
}

void AStealthGameGameMode::Handle_GameLost()
{
	OnGameOver.Broadcast(false);
	ReloadLevel();
}
