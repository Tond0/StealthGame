// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindNextPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHGAME_API UBTTask_FindNextPatrolPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector BlackboardKeyPatrolPoint;


protected:
	explicit UBTTask_FindNextPatrolPoint(FObjectInitializer const& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
