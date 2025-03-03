// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/StealthGamePlayerController.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "StealthGame/StealthGameGameMode.h"
#include "Level/Goal.h"

void AStealthGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Bind on player won
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	AStealthGameGameMode* GameMode = Cast<AStealthGameGameMode>(GameModeBase);
	FOnGameWon* OnPlayerWon = GameMode->GetOnPlayerWonDelegate();
	OnPlayerWon->AddUniqueDynamic(this, &AStealthGamePlayerController::Handle_MatchOver);
}

void AStealthGamePlayerController::Handle_MatchOver()
{
	//Disable inputs
	GetPawn()->DisableInput(this);
}