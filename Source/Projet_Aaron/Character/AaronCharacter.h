// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Projet_Aaron/Item/ObjectInteractionInterface.h"
#include "Projet_Aaron/Equipment/EquipmentInterface.h"
#include "Engine/Engine.h"
#include "Projet_Aaron/StatManager/CharacterStatManager.h"
#include "Projet_Aaron/Mechanisms/ClimbableInterface.h"
#include "Projet_Aaron/Item/AnalyseObjectInterface.h"
#include "Projet_Aaron/Item/Item.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "MyHUD.h"
//UMG
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

#include "GameFramework/Character.h"
#include "CoreMinimal.h"
#include "Projet_Aaron/Item/UInventoryCastObject.h"
#include "Projet_Aaron/Item/MainHudFixedSizeCPP.h"
#include "Projet_Aaron/Item/HUDCPP.h"
#include "Projet_Aaron/InventaireComponent.h"
#include "AaronCharacter.generated.h"

enum class EMovementState : uint8
{
	Walk,
	Run,
	Sprint,
	Climb,
	Slide
};

UCLASS()
class PROJET_AARON_API AAaronCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAaronCharacter();

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly)
		class UCameraComponent* FpsCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCharacterStatManager* StatManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* LeftArmEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* RightArmEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* HeadEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UInventaireComponent* InventaireComponent;

protected:

	FHitResult* HitGrab = nullptr;
	FHitResult* HitActor = nullptr;

	UCharacterMovementComponent* CharacterMovement;

	EMovementState MovementState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D Alignment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HoldingTimeItemWheel = 0.2f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RaycastDistanceInventory = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UUInventoryCastObject* InventoryCastObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMainHudFixedSizeCPP* MainHudFixedSizeCPP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UHUDCPP* HudCPP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUInventoryCastObject> InventoryCastObjectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UMainHudFixedSizeCPP> MainHudFixedSizeCPPClass;

	bool bPressedAlt = false;

	bool IsClimbing = false;
	bool IsLeftHandGripping = false;
	bool IsRightHandGripping = false;
	
	FVector ClimbPosition = FVector::ZeroVector;
	FVector LeftHandPosition = FVector::ZeroVector;
	FVector RightHandPosition = FVector::ZeroVector;

	float RightAxisMovement;
	float ForwardAxisMovement;

	float CurrentTimePressedItemWheel = 0.f;
	bool WheelDisplayed = false;
	
public:
	// Called every frame
	void Tick(float DeltaTime) override;

protected:
	void BeginPlay() override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector GetCharacterDirection() const;

	void UpdateSpeed();

	void MoveForward(float Value);
	void MoveRight(float Value);

	void StartJumping();

	void Walking();

	void Crouching();

	void StartSprinting();
	void StopSprinting();

	void Dodge();

	void Action();
	void StopAction();

	void ActivateHeadEquipment();

	void ActivatePressedLeft();
	void ActivateReleasedLeft();

	void ActivatePressedRight();
	void ActivateReleasedRight();

	void Climb(float DeltaTime);
	void UpdateClimbingPosition();
	bool SearchClimbPoint(FVector& ClimbPoint);

	void PressedItemWheel();
	void RepeatItemWheel();
	void ReleaseItemWheel();
	void DisplayWheel();

	UFUNCTION(BlueprintCallable)
	void UseMyItem(UDA_SlotStructure* ChosenSlot);
	void PressedUseQuickItem();
};