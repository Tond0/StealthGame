// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_FindClosestPatrolPoint.h"

#include "AI/EnemyAIController.h"
#include "NavigationSystem.h"

#include "AI/EnemyCharacter.h"
#include "AI/AIBehaviourComponent.h"
#include "AI/PatrolPoint.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Kismet/KismetMathLibrary.h"

UBTTask_FindClosestPatrolPoint::UBTTask_FindClosestPatrolPoint(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Closest Patrol Point";
}

EBTNodeResult::Type UBTTask_FindClosestPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if (!IsValid(AIController)) return EBTNodeResult::Failed;

	const APawn* AIPawn = AIController->GetPawn();
	const AEnemyCharacter* AICharacter = Cast<AEnemyCharacter>(AIPawn);
	if (!IsValid(AICharacter)) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackBoardComponent = OwnerComp.GetBlackboardComponent();

	const UAIBehaviourComponent* AIBehaviourComponent = AICharacter->GetAIBehaviourComponent();
	TConstArrayView<APatrolPoint*> PatrolPath = AIBehaviourComponent->GetPatrolPath();

	FVector AILocation = AIPawn->GetActorLocation();
	float ClosestDistance = BIG_NUMBER;
	APatrolPoint* ClosestPatrolPoint = nullptr;
	for (APatrolPoint* PatrolPoint : PatrolPath)
	{
		FVector PatrolPointLocation = PatrolPoint->GetActorLocation();
		float CurrentDistance = UKismetMathLibrary::Vector_DistanceSquared(AILocation, PatrolPointLocation);
		
		if (ClosestDistance > CurrentDistance)
		{
			ClosestDistance = CurrentDistance;
			ClosestPatrolPoint = PatrolPoint;
		}
	}

	FVector NextLocation = ClosestPatrolPoint->GetActorLocation();

	BlackBoardComponent->SetValueAsObject(BlackboardKeyPatrolPoint.SelectedKeyName, ClosestPatrolPoint);
	BlackBoardComponent->SetValueAsVector(GetSelectedBlackboardKey(), NextLocation);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
