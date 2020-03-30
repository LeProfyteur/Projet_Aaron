// Fill out your copyright notice in the Description page of Project Settings.


#include "MudAlteration.h"
#include "Projet_Aaron/AIsense/AISense_Smell.h"
#include "Projet_Aaron/AIsense/AIStimuliSourceModifier.h"

UMudAlteration::UMudAlteration()
{
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = true;
	bAutoRegister = true;
}

void UMudAlteration::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->FindComponentByClass<UAIStimuliSourceModifier>())
	{
		GetOwner()->FindComponentByClass<UAIStimuliSourceModifier>()->UnregisterFromSense(UAISense_Smell::StaticClass());
	}
}

void UMudAlteration::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMudAlteration::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	if(GetOwner()->FindComponentByClass<UAIStimuliSourceModifier>())
	{
		GetOwner()->FindComponentByClass<UAIStimuliSourceModifier>()->SetRegisterSource(UAISense_Smell::StaticClass());
	}
}