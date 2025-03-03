// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/StealthGamePlayerController.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "StealthGame/StealthGameGameMode.h"
#include "Level/Goal.h"

void AStealthGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	AStealthGameGameMode* StealthGameMode = Cast<AStealthGameGameMode>(GameModeBase);
	StealthGameMode->OnGameOver.AddUniqueDynamic(this, &AStealthGamePlayerController::Handle_OnGameOver);
}

void AStealthGamePlayerController::Handle_OnGameOver(bool IsPlayerWon)
{
	//Disable inputs
	GetPawn()->DisableInput(this);
}