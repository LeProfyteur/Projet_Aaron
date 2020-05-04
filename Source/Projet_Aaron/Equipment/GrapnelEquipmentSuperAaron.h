// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projet_Aaron/Character/GrappleHead.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Projet_Aaron/Equipment/GrapplePointer.h"
#include "Components/TimelineComponent.h"
#include "Materials/MaterialInstance.h"
#include "HookInterface.h"
#include "CableComponent.h"
#include "CoreMinimal.h"
#include "EquipmentBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GrapnelEquipmentSuperAaron.generated.h"

UCLASS()
class PROJET_AARON_API AGrapnelEquipmentSuperAaron : public AEquipmentBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrapnelEquipmentSuperAaron();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		AGrappleHead* myBullet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* hookMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UCableComponent* cable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UTimelineComponent* timeline;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector ForceDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Distance = 5000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float SwingSpeed = 100000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float RopeForce = -2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Degree = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float EndSwingLaunchZReductionFactor = 1.2f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime);

	bool isActivated = false;
	bool canHook = true;
	bool Hooked = false;
	bool foundHookSpot = false;
	bool playTLForLaser = true;
	bool IsSwing = false;

	float TimeInterpolation;

	FVector locationToGrip;
	FOnTimelineEvent updateFunction{};

public:
	virtual void Activate_Implementation(bool isPressed) override;

	UFUNCTION()
		void TimelineCallback();

	UFUNCTION()
		void AfterHook();

	UFUNCTION()
		void Hook();

	UFUNCTION()
		void Swing(float DeltaTime);

	void PlayTimeline();

};
