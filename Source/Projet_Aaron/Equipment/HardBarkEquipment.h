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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float TimeActivation = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MaxCouldown = 5.0f;

	float Couldown;

	FTimerHandle TimerHandle;

	AHardBarkEquipment();
	virtual void Activate_Implementation(bool isPressed) override;
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
		void StopEffect();
};
