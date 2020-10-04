// Fill out your copyright notice in the Description page of Project Settings.


#include "DecayingActor.h"

ADecayingActor::ADecayingActor()
{
 	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void ADecayingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeBeforeDestruction -= DeltaTime;

	if (TimeBeforeDestruction <= 0)
	{
		Destroy();
	}
}

