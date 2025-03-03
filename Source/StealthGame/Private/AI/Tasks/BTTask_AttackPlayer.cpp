// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_AttackPlayer.h"
#include "Player/PlayerCharacter.h"
#include "AIController.h"
#include "AI/EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_AttackPlayer::UBTTask_AttackPlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Attack Player";
}

EBTNodeResult::Type UBTTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoardComponent = OwnerComp.GetBlackboardComponent();
	
	UObject* PlayerObj = BlackBoardComponent->GetValueAsObject(GetSelectedBlackboardKey());
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PlayerObj);
	if (!IsValid(PlayerCharacter)) return EBTNodeResult::Failed;

	//Player Receive an Attack!
	PlayerCharacter->ReceiveAttack();

	AAIController* AIController = OwnerComp.GetAIOwner();
	ACharacter* AICharacter = AIController->GetCharacter();
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(AICharacter);

	EnemyCharacter->Attack(PlayerCharacter);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
