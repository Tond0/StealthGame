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
	
	//Bind to player death
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerCharacter);
	Player->OnPlayerDeath.AddUniqueDynamic(this, &AStealthGameHUD::Handle_OnPlayerDeath);

	//Bind to player winning
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	AStealthGameGameMode* GameMode = Cast<AStealthGameGameMode>(GameModeBase);
	FOnGameWon* OnPlayerWon = GameMode->GetOnPlayerWonDelegate();
	OnPlayerWon->AddUniqueDynamic(this, &AStealthGameHUD::Handle_OnPlayerWon);
}


void AStealthGameHUD::Handle_OnPlayerDeath()
{
	UUserWidget* WidgetDeath = CreateWidget<UUserWidget>(GetWorld(), WidgetDeathClass);
	WidgetDeath->AddToViewport();
}

void AStealthGameHUD::Handle_OnPlayerWon()
{
	UUserWidget* WidgetWon = CreateWidget<UUserWidget>(GetWorld(), WidgetWonClass);
	WidgetWon->AddToViewport();
}