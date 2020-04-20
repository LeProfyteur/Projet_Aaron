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
#include "Projet_Aaron/Equipment/NightVisionEquipment.h"
#include "Projet_Aaron/Equipment/GrapnelEquipmentSuperAaron.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Projet_Aaron/Item/Item.h"
#include "Projet_Aaron/Save/AaronGameUserSettings.h"
#include "IHeadMountedDisplay.h"
#include "PlayerAdvancement.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "MyHUD.h"
#include "Kismet/KismetMathLibrary.h"
//UMG
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

#include "GameFramework/Character.h"
#include "CoreMinimal.h"
#include "Projet_Aaron/Item/UInventoryCastObject.h"
#include "Projet_Aaron/Item/MainHudFixedSizeCPP.h"
#include "Projet_Aaron/Item/HUDCPP.h"
#include "Projet_Aaron/Item/InventaireComponent.h"
#include "AaronCharacter.generated.h"

UCLASS()
class PROJET_AARON_API AAaronCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAaronCharacter();

	/*UPROPERTY(VisibleAnywhere, BluePrintReadOnly)
		USceneComponent* VRComponent;*/

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly)
		UCameraComponent* FpsCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCharacterStatManager* StatManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UPostProcessComponent* PostProcessing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UPlayerAdvancement* PlayerAdvancement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* LeftArmEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* RightArmEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* HeadEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* ChestEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UInventaireComponent* InventaireComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTimelineComponent* VaultTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVaultAsset LowVaultAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVaultAsset HightVaultAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVaultAsset FallingVaultAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* GrapnelClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool CanVault = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RaycastDistanceInventory = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float JumpMultPercent = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxTimeGliding = 5.0f;

	bool IsGliding = false;

	//Game settings : mouse sensivity
	void AddControllerYawInput(float Val) override;
	void AddControllerPitchInput(float Val) override;

protected:

	FHitResult* HitGrab = nullptr;
	FHitResult* HitActor = nullptr;

	UCharacterMovementComponent* CharacterMovement;

	UAaronGameUserSettings* UserSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMovementState MovementState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D Alignment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HoldingTimeItemWheel = 0.2f;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DisplayTimeTips = 10.0f;

	bool bPressedAlt = false;
	bool CrouchJumped = false;
	bool IsClimbing = false;
	bool IsLeftHandGripping = false;
	bool IsRightHandGripping = false;
	bool IsInWater = false;
	bool bPressedJump = false;
	bool IsGrapnelMod = false;
	int IndexFireLeftAction;

	float WaterHeight;

	FVaultParams VaultParams;
	FVaultComponentAndTransform VaultLedgeLS;
	FVaultComponentAndTransform VaultLedgeWS;
	FTransform VaultStartOffset;
	FTransform VaultAnimatedStartOffset;

	VaultTraceSettings GroundedTraceSettings = VaultTraceSettings(250.0f, 30.0f, 75.0f, 30.0f, 30.0f);
	VaultTraceSettings FallingTraceSettings = VaultTraceSettings(150.0f, 30.0f, 70.0f, 30.0f, 30.0f);
	
	FVector ClimbPosition = FVector::ZeroVector;
	FVector LeftHandPosition = FVector::ZeroVector;
	FVector RightHandPosition = FVector::ZeroVector;
	FVector SlideRotation = FVector::ZeroVector;

	float RightAxisMovement;
	float ForwardAxisMovement;

	/* Handle to manage the timer */
	FTimerHandle GliderTimerHandle;

	float CurrentTimePressedItemWheel = 0.f;
	bool WheelDisplayed = false;

	UClass* LeftArmEquipmentClass;
	
public:
	// Called every frame
	void Tick(float DeltaTime) override;

	UFUNCTION()
		void UpdateTimelineFunction(float value);

	UFUNCTION()
		void EndTimelineFunction();

	/**
	 * \brief Update binding after changing UserSettings that change how the binding works (ie. toggle sprint)
	 */
	UFUNCTION(BlueprintCallable)
		void UpdateBindAction();

protected:
	void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector GetCharacterDirection() const;

	void UpdateSpeed();

	void MoveForward(float Value);
	void MoveRight(float Value);

	void StartJumping();
	void EndJumping();
    
	void ToggleWalk();
	void ToggleSprint();

	UFUNCTION(BlueprintCallable)
	void ToggleCrouch();

	void StartSprinting();
	void StopSprinting();

	void Dodge();

	void Interact();
	void StopInteract();

	UFUNCTION(BlueprintCallable)
	void ActivateHeadEquipment();

	UFUNCTION(BlueprintCallable)
	void ActivatePressedLeft();

	UFUNCTION(BlueprintCallable)
	void ActivateReleasedLeft();

	UFUNCTION(BlueprintCallable)
	void ActivatePressedRight();

	UFUNCTION(BlueprintCallable)
	void ActivateReleasedRight();

	UFUNCTION(BlueprintCallable)
	void EnableDisableNightVision();

	UFUNCTION(BlueprintCallable)
		void EnableDisableGrapnel();

	UFUNCTION(BlueprintCallable)
		void ActivatePressedChest();

	void Climb(float DeltaTime);
	void UpdateClimbingPosition();
	bool SearchClimbPoint(FVector& ClimbPoint);

	void Scan();
	void ScanRelease();

	void PressedItemWheel();
	void ReleaseItemWheel();
	void DisplayWheel();

	UFUNCTION(BlueprintCallable)
	void UseMyItem(UDA_SlotStructure* ChosenSlot);
	void PressedUseQuickItem();

	bool VaultCheck(VaultTraceSettings TraceSettings);
	void VaultStart(float VaultHeight, VaultType VaultType);

	bool FindWallToClimb(VaultTraceSettings TraceSettings, FVector& InitialTraceImpactPoint, FVector& InitialTraceNormal);
	bool CanClimbOnWall(VaultTraceSettings TraceSettings, FVector& InitialTraceImpactPoint, FVector& InitialTraceNormal, float& VaultHeight, VaultType& Vault);
	bool CapsuleHasRoomCheck(FVector TargetLocation, float HeightOffset, float RadiusOffset);
	FVaultComponentAndTransform ConvertWorldToLocal(FVaultComponentAndTransform WorldSpaceVault);
	FVaultComponentAndTransform ConvertLocalToWorld(FVaultComponentAndTransform LocalSpaceVault);
	FVaultParams GetVaultParam(VaultType Vault, float VaultHeight);
	FTransform GetVaultStartOffset(FTransform& VaultTarget);
	FTransform GetVaultAnimatedStartOffset(FVaultParams& VaultParam, FTransform& VaultTarget);
	FVector GetCapsuleBaseLocation(float ZOffset) const;
	FVector GetCapsuleBaseLocationFromBase(FVector BaseLocation, float ZOffset) const;

	FOnTimelineFloat UpdateTimeline{};
	FOnTimelineEvent FinishTimeLine{};
};