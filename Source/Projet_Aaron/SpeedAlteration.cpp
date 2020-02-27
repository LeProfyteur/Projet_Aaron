// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedAlteration.h"

// Sets default values for this component's properties
USpeedAlteration::USpeedAlteration()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	TimeAlteration = TimeMutation;

	// ...
}


// Called when the game starts
void USpeedAlteration::BeginPlay()
{
	Super::BeginPlay();

	_CreatureStatManager = GetOwner()->FindComponentByClass<UCreatureStatManager>();
	BaseSpeed = _CreatureStatManager->GetBaseSpeed();
	SpeedReducted = BaseSpeed/4.0f;
	_CreatureStatManager->SetActualSpeed(SpeedReducted);
	GetWorld()->GetTimerManager().SetTimer(InputTimeHandle, this, &USpeedAlteration::ReductionSpeed, 1.0f, true, 0.5f);
	
}


// Called every frame
void USpeedAlteration::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpeedAlteration::ReductionSpeed()
{
	if (TimeAlteration <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(InputTimeHandle);
		_CreatureStatManager->ResetSpeed();
	}
	TimeAlteration -= 1.0f;
}
