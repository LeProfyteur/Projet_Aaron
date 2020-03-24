// Fill out your copyright notice in the Description page of Project Settings.


#include "StiltEquipment.h"

AStiltEquipment::AStiltEquipment() : Super() {}

void AStiltEquipment::Activate_Implementation(bool isPressed)
{
	if (isPressed)
	{

	}
}

void AStiltEquipment::OnEquip_Implementation(FCharacterSkills &Skills)
{
	Skills.Stilt = true;
}

void AStiltEquipment::OnUnequip_Implementation(FCharacterSkills &Skills)
{
	Skills.Stilt = false;
}

