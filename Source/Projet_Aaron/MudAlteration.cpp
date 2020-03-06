// Fill out your copyright notice in the Description page of Project Settings.


#include "MudAlteration.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "AISense_Smell.h"

UMudAlteration::UMudAlteration()
{
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = true;
	bAutoRegister = true;
}

void UMudAlteration::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->FindComponentByClass<UAIPerceptionStimuliSourceComponent>())
	{
		GetOwner()->FindComponentByClass<UAIPerceptionStimuliSourceComponent>()->UnregisterFromSense(UAISense_Smell::StaticClass());
	}
}

void UMudAlteration::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMudAlteration::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	if(GetOwner()->FindComponentByClass<UAIPerceptionStimuliSourceComponent>())
	{
		GetOwner()->FindComponentByClass<UAIPerceptionStimuliSourceComponent>()->RegisterAsSourceForSenses.Add(UAISense_Smell::StaticClass());
	}
}








