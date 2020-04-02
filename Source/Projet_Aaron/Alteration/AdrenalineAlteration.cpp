// Fill out your copyright notice in the Description page of Project Settings.


#include "AdrenalineAlteration.h"

UAdrenalineAlteration::UAdrenalineAlteration()
{

}

void UAdrenalineAlteration::BeginPlay()
{
	Super::BeginPlay();
	_CreatureStatManager = GetOwner()->FindComponentByClass<UCreatureStatManager>();
	if (_CreatureStatManager)
	{
		_CreatureStatManager->SetbAdrenalineBoost(true);
	}

	
}

void UAdrenalineAlteration::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	if (_CreatureStatManager)
	{
		_CreatureStatManager->SetbAdrenalineBoost(false);
	}
}
