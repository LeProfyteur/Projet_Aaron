// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentBase.h"
#include "GliderEquipment.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API AGliderEquipment : public AEquipmentBase
{
	GENERATED_BODY()

public:
	void OnEquip_Implementation(FCharacterSkills Skills) override;
	void OnUnequip_Implementation(FCharacterSkills Skills) override;
};
