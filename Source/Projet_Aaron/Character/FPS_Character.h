// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Projet_Aaron/Item/ObjectInteractionInterface.h"
#include "Projet_Aaron/Equipment/EquipmentInterface.h"
#include "Engine/Engine.h"
#include "Projet_Aaron/StatManager/CharacterStatManager.h"

#include "GameFramework/Character.h"
#include "CoreMinimal.h"
#include "FPS_Character.generated.h"

UCLASS()
class PROJET_AARON_API AFPS_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPS_Character();

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly)
	class UCameraComponent* FpsCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCharacterStatManager* StatManager;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsNearClimbing = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* LeftArmEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* RightArmEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* HeadEquipment;

protected:

	FHitResult* HitGrab = nullptr;
	FHitResult* HitActor = nullptr;

	bool IsSprinting = false;
	bool bPressedAlt = false;

	float RightAxisMovement;
	float ForwardAxisMovement;
	
	virtual void BeginPlay() override;
	void CharacterMove();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	
	void StartJump();
	
	void Sprint();
	void StopSprint();

	void StartAlt();
	void StopAlt();

	void Crouching();
	void Dodge(FVector direction);
	void Climb(float value);

	void Action();
	void StopAction();
	void Analyse();

	void ActivatePressedLeft();
	void ActivateReleasedLeft();

	void ActivatePressedRight();
	void ActivateReleasedRight();

	void ActivateHeadEquipment();

	UFUNCTION(BlueprintCallable) void StopClimbing();

};
