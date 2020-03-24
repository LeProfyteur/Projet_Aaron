// Fill out your copyright notice in the Description page of Project Settings.


#include "GliderEquipment.h"

void AGliderEquipment::OnEquip_Implementation(FCharacterSkills &Skills)
{
	Skills.Glider = true;
}

void AGliderEquipment::OnUnequip_Implementation(FCharacterSkills &Skills)
{
	Skills.Glider = false;
}
