// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/Level/Goal.h"
#include "StealthGameGameMode.generated.h"

UCLASS(minimalapi)
class AStealthGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	FTimerHandle NextTickTimer;	

//Goal
protected:
	UPROPERTY(BlueprintReadOnly)
	AGoal* Goal;

public:
	FOnGameWon* GetOnPlayerWonDelegate() const { return &Goal->OnGameWon; }

protected:
	UFUNCTION(BlueprintCallable, meta = (BlueprintProtected))
	void ReloadLevel();
	
	UFUNCTION()
	void Handle_TimerEnded();

public:
	AStealthGameGameMode();
	void BeginPlay() override;
};



