// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE(FOnGoalReached);

class UBoxComponent;

UCLASS()
class STEALTHGAME_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FOnGoalReached OnGoalReached;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UBoxComponent* BoxCheck;

public:	
	// Sets default values for this actor's properties
	AGoal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
