// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperJumpEquipment.h"

void ASuperJumpEquipment::OnEquip_Implementation(FCharacterSkills Skills)
{
	Skills.SuperJump = true;
}

void ASuperJumpEquipment::OnUnequip_Implementation(FCharacterSkills Skills)
{
	Skills.SuperJump = false;
}
