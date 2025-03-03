// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StealthGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHGAME_API AStealthGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	void BeginPlay() override;

	UFUNCTION()
	void Handle_OnGameOver(bool IsPlayerWon);

};
