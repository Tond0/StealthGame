// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StealthGameCharacter.h"
#include "EnemyCharacter.generated.h"

class UAIBehaviourComponent;
class UBlackboardComponent;

UCLASS()
class STEALTHGAME_API AEnemyCharacter : public AStealthGameCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BlueprintProtected))
	UAIBehaviourComponent* AIBehaviourComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BlueprintProtected))
	UBlackboardComponent* BlackBoardComponent;

public:
	void Attack(AStealthGameCharacter* CharacterToAttack);
	void ReceiveAttack() override;
	UFUNCTION(BlueprintCallable)
	bool CanBeAttacked();

//Getters
public:
	const UAIBehaviourComponent* GetAIBehaviourComponent() const { return AIBehaviourComponent; };
	const UBlackboardComponent* GetBlackBoardComponent() const { return BlackBoardComponent; };
};
