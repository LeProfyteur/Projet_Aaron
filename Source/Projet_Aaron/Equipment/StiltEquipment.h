// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UCurveFloat* FloatHeightCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UTimelineComponent* timeline;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Height = 50.0f;

	bool isActivate = false;

	FOnTimelineFloat updateHeightFunction{};

	AStiltEquipment();
	virtual void Activate_Implementation(bool isPressed) override;
	virtual void OnEquip_Implementation(FCharacterSkills& Skills) override;
	virtual void OnUnequip_Implementation(FCharacterSkills& Skills) override;

	UFUNCTION()
		void UpdateHeight(float value);

protected:

	FVector StartPos = FVector::ZeroVector;

	virtual void BeginPlay() override;
};
