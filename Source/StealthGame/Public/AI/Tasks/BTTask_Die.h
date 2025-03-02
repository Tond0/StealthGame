// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Die.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHGAME_API UBTTask_Die : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	explicit UBTTask_Die(FObjectInitializer const& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
