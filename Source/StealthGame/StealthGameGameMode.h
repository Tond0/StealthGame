// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/Level/Goal.h"
#include "StealthGameGameMode.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOver, bool, PlayerWon);

UCLASS(minimalapi)
class AStealthGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnGameOver OnGameOver;

private:
	FTimerHandle NextTickTimer;	

protected:
	UFUNCTION(BlueprintCallable, meta = (BlueprintProtected))
	void ReloadLevel();
	
	UFUNCTION()
	void Handle_TimerEnded();

public:
	UFUNCTION(BlueprintCallable)
	void SetGoal(AGoal* CurrentGoal);
	UFUNCTION(BlueprintCallable)
	void SetPlayer(APlayerCharacter* NewPlayerCharacter);

protected:
	UFUNCTION(meta = (BlueprintProtected))
	void Handle_GameWon();
	UFUNCTION(meta = (BlueprintProtected))
	void Handle_GameLost();

public:
	AStealthGameGameMode();
};



