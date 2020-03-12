// Fill out your copyright notice in the Description page of Project Settings.


#include "AdrenalineAlteration.h"

UAdrenalineAlteration::UAdrenalineAlteration()
{

}

void UAdrenalineAlteration::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->FindComponentByClass<UCreatureStatManager>())
	{
		GetOwner()->FindComponentByClass<UCreatureStatManager>()->SetbAdrenalineBoost(true);
	}

	
}

void UAdrenalineAlteration::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	if (GetOwner()->FindComponentByClass<UCreatureStatManager>())
	{
		GetOwner()->FindComponentByClass<UCreatureStatManager>()->SetbAdrenalineBoost(false);
	}
}
