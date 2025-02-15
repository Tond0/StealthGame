// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "GameFramework/Character.h"

#include "Kismet/GameplayStatics.h"


AEnemyAIController::AEnemyAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	//Bind Events
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AEnemyAIController::Handle_OnPerceptionUpdated);

	//Run the base behaviour tree.
	RunBehaviorTree(BTEnemy);
}


void AEnemyAIController::Handle_OnPerceptionUpdated(AActor* TargetActor, FAIStimulus Stimulus)
{
	//Check is Sight Stimulus
	//TSubclassOf<UAISense> StimulusClass = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus);
	//if (!Cast<UAISense_Sight>(StimulusClass)) return;

	//Check we saw the player
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (TargetActor == Cast<AActor>(PlayerCharacter))
	{
		//GetBlackBoard Component and Key
		UBlackboardComponent* BlackBoard = GetBlackboardComponent();
		FName BlackBoardPlayerKey = "Player";

		if (Stimulus.WasSuccessfullySensed())
		{
			//If we did see the player we set this as the player
			Blackboard->SetValueAsObject(BlackBoardPlayerKey, Cast<UObject>(TargetActor));
		}
		else
		{
			//If we did NOT see the player we return nullptr.
			Blackboard->SetValueAsObject(BlackBoardPlayerKey, nullptr);
		}
	}
}