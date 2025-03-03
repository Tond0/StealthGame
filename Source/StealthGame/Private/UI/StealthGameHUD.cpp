// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StealthGameHUD.h"

#include "Kismet/GameplayStatics.h"
#include "StealthGame/StealthGameGameMode.h"
#include "UI/Widgets/WidgetDeath.h"
#include "Level/Goal.h"
#include "Player/PlayerCharacter.h"

void AStealthGameHUD::BeginPlay()
{
	Super::BeginPlay();
	
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	AStealthGameGameMode* StealthGameMode = Cast<AStealthGameGameMode>(GameModeBase);
	StealthGameMode->OnGameOver.AddUniqueDynamic(this, &AStealthGameHUD::Handle_OnGameOver);
}

void AStealthGameHUD::Handle_OnGameOver(bool IsPlayerWon)
{
	UUserWidget* WidgetGameOver = nullptr;
	
	if(IsPlayerWon)
		WidgetGameOver = CreateWidget<UUserWidget>(GetWorld(), WidgetWonClass);
	else
		WidgetGameOver = CreateWidget<UUserWidget>(GetWorld(), WidgetDeathClass);

	WidgetGameOver->AddToViewport();
}