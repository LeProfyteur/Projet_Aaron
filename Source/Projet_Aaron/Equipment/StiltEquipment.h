// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentBase.h"
#include "StiltEquipment.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API AStiltEquipment : public AEquipmentBase
{
	GENERATED_BODY()

public:

<<<<<<< HEAD
	AStiltEquipment();
	virtual void Activate_Implementation(bool isPressed) override;
	virtual void OnEquip_Implementation(FCharacterSkills &Skills) override;
	virtual void OnUnequip_Implementation(FCharacterSkills &Skills) override;
=======
	virtual void OnEquip_Implementation(FCharacterSkills Skills) override;
	virtual void OnUnequip_Implementation(FCharacterSkills Skills) override;
>>>>>>> dev
};
