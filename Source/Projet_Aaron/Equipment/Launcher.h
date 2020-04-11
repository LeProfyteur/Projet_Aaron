// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "EquipmentBase.h"
#include "TimerManager.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Projet_Aaron/Character/AaronCharacter.h"
#include "Launcher.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API ALauncher : public AEquipmentBase
{
	GENERATED_BODY()

public:
	ALauncher();
	
	UPROPERTY(EditAnywhere)
		USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere)
		UClass* ProjectileClass;

	UPROPERTY(EditAnywhere)
		float Cooldown = 1.0f;

	UPROPERTY(EditAnywhere)
		float Distance = 2000.0f;

protected:
	FTimerHandle CooldownTimerHandle;
	bool Aiming;
	bool ReadyToFire;

public:
	void Activate_Implementation(bool isPressed) override;

protected:
	UFUNCTION()
		void CooldownReady();
};
