// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

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
	//Check we saw the player
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (TargetActor != Cast<AActor>(PlayerCharacter)) return;


	//GetBlackBoard Component and Key
	UBlackboardComponent* BlackBoard = GetBlackboardComponent();
	FName BlackBoardPlayerKey = "Player";
	FName BlackBoardStimulusLocationKey = "StimulusLocation";

	//Check is Sight Stimulus
	TSubclassOf<UAISense> StimulusClass = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus);


	//Are we trying to update the Sight?
	if (StimulusClass == UAISense_Sight::StaticClass())
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			//AI knows player is around.
			Blackboard->SetValueAsObject(BlackBoardPlayerKey, Cast<UObject>(TargetActor));
			IsBeingSpotted = true;

			//We don't need to investigate anything. We see it lol.
			Blackboard->ClearValue(BlackBoardStimulusLocationKey);
		}
		else
		{
			//If we do NOT see the player anymore, we need to investigate last location.
			Blackboard->SetValueAsVector(BlackBoardStimulusLocationKey, Stimulus.StimulusLocation);
			IsBeingSpotted = false;
		}
	}
	//Are we trying to update Hearing?
	else if (StimulusClass == UAISense_Hearing::StaticClass())
	{
		//If Player is already being spotted, then we don't care about the hearing.
		if (IsBeingSpotted) return;

		//If we do hear the player...
		if (Stimulus.WasSuccessfullySensed())
		{
			//AI knows player is around.
			Blackboard->SetValueAsObject(BlackBoardPlayerKey, Cast<UObject>(TargetActor));

			//AI is now investigating the location of the noise.
			Blackboard->SetValueAsVector(BlackBoardStimulusLocationKey, Stimulus.StimulusLocation);
		}
	}
}