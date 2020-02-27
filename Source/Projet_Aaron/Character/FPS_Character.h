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

#include "GameFramework/Character.h"
#include "CoreMinimal.h"
#include "Projet_Aaron/Item/UInventoryCastObject.h"
#include "Projet_Aaron/Item/MainHudFixedSizeCPP.h"
#include "Projet_Aaron/Item/HUDCPP.h"
#include "Projet_Aaron/InventaireComponent.h"
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

	bool IsSprinting = false;
	bool IsClimbing = false;
	bool IsLeftHandGripping = false;
	bool IsRightHandGripping = false;
	

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAnchors AnchorsCastWidget;*/
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAnchors AnchorsInventoryWindow;*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Alignment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RaycastDistanceInventory = 1000.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		class UUInventoryCastObject* InventoryCastObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMainHudFixedSizeCPP* MainHudFixedSizeCPP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UHUDCPP* HudCPP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUInventoryCastObject> InventoryCastObjectClass;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		TSubclassOf<class UMainHudFixedSizeCPP> MainHudFixedSizeCPPClass;

	bool bPressedAlt = false;

	FVector ClimbPosition = FVector::ZeroVector;
	FVector LeftHandPosition = FVector::ZeroVector;
	FVector RightHandPosition = FVector::ZeroVector;

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

	void Action();
	void StopAction();
	void Analyse();

	void ActivatePressedLeft();
	void ActivateReleasedLeft();

	void ActivatePressedRight();
	void ActivateReleasedRight();
	
	void PressedItemWheel();
	void ReleaseItemWheel();

	void ActivateHeadEquipment();

	UFUNCTION(BlueprintCallable)
	void UseMyItem(UDA_SlotStructure* ChosenSlot);
	void PressedUseQuickItem();

	UFUNCTION(BlueprintCallable)
		void ResetAdrenalineBoost();

protected :
	void CharacterClimb(float DeltaTime);
	void UpdateClimbingPosition();
	bool SearchClimbPoint(FVector& ClimbPoint);
};
