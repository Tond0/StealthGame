// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_MoveToRandomLocation.h"

#include "AI/EnemyAIController.h"
#include "NavigationSystem.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_MoveToRandomLocation::UBTTask_MoveToRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location";
}

EBTNodeResult::Type UBTTask_MoveToRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!IsValid(AIController)) return EBTNodeResult::Failed;

	AEnemyAIController* const EnemyAIController = Cast<AEnemyAIController>(AIController);
	if (!IsValid(EnemyAIController)) return EBTNodeResult::Failed;
	
	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!IsValid(NavSystem)) return EBTNodeResult::Failed;
	
	FVector Origin = AIController->GetPawn()->GetActorLocation();
	FNavLocation Location;
	NavSystem->GetRandomPointInNavigableRadius(Origin, 500, Location);
	if (!IsValid(NavSystem)) return EBTNodeResult::Failed;
	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Location.Location);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
