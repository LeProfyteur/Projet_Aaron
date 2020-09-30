// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Projet_Aaron/Equipment/EquipmentInterface.h"
#include "Engine/Engine.h"
#include "Projet_Aaron/StatManager/CharacterStatManager.h"
#include "Projet_Aaron/Mechanisms/ClimbableInterface.h"
#include "Projet_Aaron/Equipment/NightVisionEquipment.h"
#include "Projet_Aaron/Equipment/GrapnelEquipmentSuperAaron.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Projet_Aaron/Save/AaronGameUserSettings.h"
#include "IHeadMountedDisplay.h"
#include "Projet_Aaron/Mutation/UMutationBase.h"
#include "Projet_Aaron/Equipment/EquipmentBase.h"
#include "PlayerAdvancementSubsystem.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMathLibrary.h"

#include "GameFramework/Character.h"
#include "AaronCharacter.generated.h"

UCLASS()
class PROJET_AARON_API AAaronCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAaronCharacter();

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly)
		UCameraComponent* FpsCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCharacterStatManager* StatManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UPostProcessComponent* PostProcessing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* LeftArmEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* RightArmEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* HeadEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* ChestEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* LegsEquipment;

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
		UTimelineComponent* PoisonTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTimelineComponent* LsdTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTimelineComponent* DodgeTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* CurvePoison;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* CurveLSD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* CurveDodge;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isJumping = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAimingLeft = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAimingRight = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isPunctionning = false;

	bool IsGliding = false;
protected:

	TArray<UUMutationBase*> Mutations;
	FHitResult* HitActor = nullptr;

	UAaronGameUserSettings* UserSettings;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D Alignment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HoldingTimeItemWheel = 0.2f;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DodgeDistance = 1000.0f;
	bool CanDodge = true;
	FVector LocationBeforeDodge;
	FVector LocationAfterDodge;

	float WaterHeight;

	float VaultHeight;
	VaultType VaultType;
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
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void UpdateTimelineFunction(float value);

	UFUNCTION()
		void UpdateTimelinePoisonFunction(float value);

	UFUNCTION()
		void UpdateTimelineLSDFunction(float value);

	UFUNCTION()
		void EndTimelineFunction();

	void OnPoisonAlteration();
	void OnLsdAlteration(float Time);

protected:
	void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector GetCharacterDirection() const;

	void UpdateSpeed();

	UFUNCTION(BlueprintCallable)
		void StartJumping();	
	UFUNCTION(BlueprintCallable)
		void EndJumping();
	UFUNCTION()
		void OnLandedCallback(const FHitResult& Hit);
	
	UFUNCTION(BlueprintCallable)
		void StartCrouching();
	UFUNCTION(BlueprintCallable)
		void StopCrouching();

	UFUNCTION(BlueprintCallable)
		void StartSprinting();
	UFUNCTION(BlueprintCallable)
		void StopSprinting();

	UFUNCTION(BlueprintCallable)
		void Dodge();
	UFUNCTION(BlueprintCallable)
		void SetDodgeLocation(float Value);
	UFUNCTION(BlueprintCallable)
		void ResetDodge();
	FVector GetActorLocationAfterDodge(float Distance);

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

	UFUNCTION(BlueprintCallable)
		void AddEquipment(UChildActorComponent* PartChild, TSubclassOf<AEquipmentBase> ClassEquipment);

	UFUNCTION(BlueprintCallable)
		void RemoveEquipment(UChildActorComponent* PartChild, TSubclassOf<AEquipmentBase> ClassEquipment);

	UFUNCTION(BlueprintCallable)
		void AddMutation(TSubclassOf<UUMutationBase> Mutation);

	UFUNCTION(BlueprintCallable)
		void RemoveMutation(UClass *ClassMutation);

	void Climb(float DeltaTime);
	void UpdateClimbingPosition();
	bool SearchClimbPoint(FVector& ClimbPoint);

	bool VaultCheck(VaultTraceSettings TraceSettings);
	void VaultStart();

	bool FindWallToClimb(VaultTraceSettings TraceSettings, FVector& InitialTraceImpactPoint, FVector& InitialTraceNormal);
	bool CanClimbOnWall(VaultTraceSettings TraceSettings, FVector& InitialTraceImpactPoint, FVector& InitialTraceNormal);
	bool CapsuleHasRoomCheck(FVector TargetLocation, float HeightOffset, float RadiusOffset);
	FVaultComponentAndTransform ConvertWorldToLocal(FVaultComponentAndTransform WorldSpaceVault);
	FVaultComponentAndTransform ConvertLocalToWorld(FVaultComponentAndTransform LocalSpaceVault);
	FVaultParams GetVaultParam();
	FTransform GetVaultStartOffset(FTransform& VaultTarget);
	FTransform GetVaultAnimatedStartOffset(FVaultParams& VaultParam, FTransform& VaultTarget);
	FVector GetCapsuleBaseLocation(float ZOffset) const;
	FVector GetCapsuleBaseLocationFromBase(FVector BaseLocation, float ZOffset) const;

	FOnTimelineFloat UpdateTimeline{};
	FOnTimelineEvent FinishTimeLine{};
	FOnTimelineFloat UpdateTimelinePoison{};
	FOnTimelineFloat UpdateTimelineLSD{};
	FOnTimelineFloat UpdateDodgeTimeline{};
	FOnTimelineEvent FinishDodgeTimeLine{};

private:
	void ResolveMovementMethod();
	EMovementMethod CurrentMovementMethod = EMovementMethod::Run;
	EMovementMethod DesiredMovementMethod = EMovementMethod::Run;
};
