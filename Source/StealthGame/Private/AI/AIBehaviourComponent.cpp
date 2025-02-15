// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIBehaviourComponent.h"

// Sets default values for this component's properties
UAIBehaviourComponent::UAIBehaviourComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAIBehaviourComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIBehaviourComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAIBehaviourComponent::UpdateToNextPatrolPoint(APatrolPoint*& CurrentPatrolPoint) const
{
	//If its nullptr something went wrong.
	if (!CurrentPatrolPoint) return;

	int index = PatrolPath.Find(CurrentPatrolPoint);

	if (PatrolPath.Num() <= index + 1)
	{
		index = 0;
	}
	else
	{
		index += 1;
	}

	CurrentPatrolPoint = PatrolPath[index];
}

