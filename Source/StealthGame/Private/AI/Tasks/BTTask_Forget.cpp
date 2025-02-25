// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Forget.h"

#include "BehaviorTree/BlackboardComponent.h"


UBTTask_Forget::UBTTask_Forget(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Forget";
}

//Player? What Player? Dunno nothin about it.
EBTNodeResult::Type UBTTask_Forget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoardComponent = OwnerComp.GetBlackboardComponent();
	BlackBoardComponent->SetValueAsObject(GetSelectedBlackboardKey(), nullptr);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
