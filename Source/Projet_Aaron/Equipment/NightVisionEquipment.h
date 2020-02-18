// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PostProcessComponent.h"
#include "CoreMinimal.h"
#include "EquipmentBase.h"
#include "NightVisionEquipment.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API ANightVisionEquipment : public AEquipmentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANightVisionEquipment();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UPostProcessComponent* postProcess;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool isActivated = false;

public:
	virtual void Activate_Implementation() override;
	//virtual void OnEquip_Implementation() override;
	//virtual void OnUnequip_Implementation() override;
};
