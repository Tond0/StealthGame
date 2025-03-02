// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_FindNextPatrolPoint.h"

#include "AI/EnemyAIController.h"
#include "NavigationSystem.h"

#include "AI/EnemyCharacter.h"
#include "AI/AIBehaviourComponent.h"
#include "AI/PatrolPoint.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindNextPatrolPoint::UBTTask_FindNextPatrolPoint(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Next Patrol Point";
}

EBTNodeResult::Type UBTTask_FindNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if (!IsValid(AIController)) return EBTNodeResult::Failed;

	const APawn* AIPawn = AIController->GetPawn();
	const AEnemyCharacter* AICharacter = Cast<AEnemyCharacter>(AIPawn);
	if (!IsValid(AICharacter)) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackBoardComponent = OwnerComp.GetBlackboardComponent();

	const UAIBehaviourComponent* AIBehaviourComponent = AICharacter->GetAIBehaviourComponent();

	APatrolPoint* PatrolPoint = Cast<APatrolPoint>(BlackBoardComponent->GetValueAsObject(GetSelectedBlackboardKey()));
	AIBehaviourComponent->UpdateToNextPatrolPoint(PatrolPoint);
	FVector NextLocation = PatrolPoint->GetActorLocation();

	BlackBoardComponent->SetValueAsObject(GetSelectedBlackboardKey(), PatrolPoint);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
