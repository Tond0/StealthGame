// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "StealthGameCharacter.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

//NOTE: THIS IS NOW USED AS A SHARED ABSTRACT CLASS BETWEEN PLAYERCHARACTER AND ENEMYCHARACTER.
UCLASS(config=Game, Abstract)
class AStealthGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AStealthGameCharacter();
	
protected:
	UPROPERTY(BlueprintReadWrite)
	bool IsAttacking;

public:
	UFUNCTION(BlueprintCallable)
	virtual void ReceiveAttack() { return; };
};

