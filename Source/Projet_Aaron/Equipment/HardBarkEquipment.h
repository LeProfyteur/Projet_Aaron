// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentBase.h"
#include "Projet_Aaron/Character/AaronCharacter.h"
#include "HardBarkEquipment.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API AHardBarkEquipment : public AEquipmentBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
		float TimeActivation = 1.0f;

	FTimerHandle TimerHandle;

	AHardBarkEquipment();
	virtual void Activate_Implementation(bool isPressed) override;
	virtual void OnEquip_Implementation(FCharacterSkills Skills) override;
	virtual void OnUnequip_Implementation(FCharacterSkills Skills) override;
	
	UFUNCTION()
		void StopEffect();
};
