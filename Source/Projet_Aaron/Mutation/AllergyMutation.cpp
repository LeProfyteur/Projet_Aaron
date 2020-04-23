// Fill out your copyright notice in the Description page of Project Settings.


#include "AllergyMutation.h"

UAllergyMutation::UAllergyMutation()
{
	Super();
}

void UAllergyMutation::OnEquip(FCharacterSkills& Skills)
{
	Skills.Allergy = true;
}

void UAllergyMutation::OnUnEquip(FCharacterSkills& Skills)
{
	Skills.Allergy = false;
}
