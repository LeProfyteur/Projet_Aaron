// Fill out your copyright notice in the Description page of Project Settings.


#include "PoisonAlteration.h"

// Sets default values for this component's properties
UPoisonAlteration::UPoisonAlteration()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UPoisonAlteration::BeginPlay()
{
	Super::BeginPlay();
	TimeAlteration = TimeMutation;
	_statManager = GetOwner()->FindComponentByClass<UStatManager>();
	if (_statManager)
	{
		DamageOverTime();
	}
	
}

// Called every frame
void UPoisonAlteration::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UPoisonAlteration::DamageOverTime()
{
	UWorld* World = GetWorld();
	World->GetTimerManager().SetTimer(InputTimeHandle, this, &UPoisonAlteration::TakeDamage, 1.0f, true, 0.5f);
	_statManager->TakeDamage(PoisonDamageBio, PoisonDamageTech);
}


void UPoisonAlteration::TakeDamage()
{
	if (TimeAlteration <= 1.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(InputTimeHandle);
	}
	
	TimeAlteration -= 1.0f;
	_statManager->TakeDamage(PoisonDamageBio, PoisonDamageTech);
}
