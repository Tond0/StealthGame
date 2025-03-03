// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class UAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class STEALTHGAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
	AEnemyAIController();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BlueprintProtected))
	UBehaviorTree* BTEnemy;

//AI Perception
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BlueprintProtected))
	UAIPerceptionComponent* AIPerceptionComponent;;

	UPROPERTY(BlueprintReadOnly, meta = (BlueprintProtected))
	bool IsBeingSpotted;
	

	UFUNCTION()
	void Handle_OnPerceptionUpdated(AActor* TargetActor, FAIStimulus Stimulus);

protected:
	UFUNCTION()
	virtual void BeginPlay() override;
	UFUNCTION()
	void Handle_OnPlayerDeath();
	UFUNCTION()
	void Handle_OnGameWon();
};
