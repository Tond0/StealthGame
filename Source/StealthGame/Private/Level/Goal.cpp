// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Goal.h"
#include "Components/BoxComponent.h"

// Sets default values
AGoal::AGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCheck = CreateDefaultSubobject<UBoxComponent>("Goal Collision Check");
	SetRootComponent(BoxCheck);
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCheck->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGoal::OnBoxBeginOverlap);
}

void AGoal::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnGameWon.Broadcast();
}

// Called every frame
void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

