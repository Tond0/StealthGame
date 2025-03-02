// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Die.h"

#include "AIController.h"

UBTTask_Die::UBTTask_Die(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Die";
}


EBTNodeResult::Type UBTTask_Die::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIOwner->GetPawn();
	AIPawn->Destroy();

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}