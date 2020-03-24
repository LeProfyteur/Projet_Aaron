// Fill out your copyright notice in the Description page of Project Settings.


#include "StiltEquipment.h"

void AStiltEquipment::OnEquip_Implementation(FCharacterSkills Skills)
{
	Skills.Stilt = true;
}

void AStiltEquipment::OnUnequip_Implementation(FCharacterSkills Skills)
{
	Skills.Stilt = false;
}

