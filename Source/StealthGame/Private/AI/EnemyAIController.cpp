// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyAIController.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	//Run the base behaviour tree.
	RunBehaviorTree(BTEnemy);
}