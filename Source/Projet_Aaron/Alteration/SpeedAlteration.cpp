// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedAlteration.h"

// Sets default values for this component's properties
USpeedAlteration::USpeedAlteration()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void USpeedAlteration::BeginPlay()
{
	Super::BeginPlay();
	TimeAlteration = TimeMutation;
	_CreatureStatManager = GetOwner()->FindComponentByClass<UCreatureStatManager>();

	if (_CreatureStatManager)
	{
		_CreatureStatManager->SetSpeedAlteration(true);
		_CreatureStatManager->AddSpeedMultiplier(SpeedReduction);
	}
}


// Called every frame
void USpeedAlteration::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogActor, Warning, TEXT("TimeAlteration : %f"), TimeAlteration);
	// ...
}

void USpeedAlteration::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	if (_CreatureStatManager)
	{
		_CreatureStatManager->SetSpeedAlteration(false);

		_CreatureStatManager->AddSpeedMultiplier(-SpeedReduction);
	}
}

/*
void USpeedAlteration::ReductionSpeed()
{
	UE_LOG(LogActor, Error, TEXT("TimeAlteration : %f"),TimeAlteration);
	if (TimeAlteration <= 1.0)
	{
		GetWorld()->GetTimerManager().ClearTimer(InputTimeHandle);
		_CreatureStatManager->AddSpeedMultiplier(-SpeedReduction);
	}
	TimeAlteration -= 1.0f;
	
}
*/
