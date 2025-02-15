// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIBehaviourComponent.generated.h"

class APatrolPoint;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEALTHGAME_API UAIBehaviourComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIBehaviourComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BlueprintProtected));
	TArray<APatrolPoint*> PatrolPath;

//Getters
public:
	TConstArrayView<APatrolPoint*> GetPatrolPath() const { return PatrolPath; }

	/// <summary>
	/// Update the current patrol point to the next one.
	/// </summary>
	/// <param name="CurrentPatrolPoint">The current patrol point.</param>
	UFUNCTION(BlueprintCallable)
	void UpdateToNextPatrolPoint(APatrolPoint*& CurrentPatrolPoint) const;
};
