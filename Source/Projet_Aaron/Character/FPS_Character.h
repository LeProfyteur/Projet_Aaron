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

#include "GameFramework/Character.h"
#include "CoreMinimal.h"
#include "Projet_Aaron/Item/UInventoryCastObject.h"
#include "Projet_Aaron/Item/MainHudFixedSizeCPP.h"
#include "Projet_Aaron/Item/HUDCPP.h"
#include "Projet_Aaron/InventaireComponent.h"
#include "FPS_Character.generated.h"

enum class EMovement : uint8
{
	Forward,
	Right
};

enum class VaultType : uint8
{
	HighVault,
	LowVault,
	FallingCatch
};

enum class EStateMovement : uint8
{
	Walk,
	Run,
	Sprint
};

struct FVaultComponentAndTransform
{
	UPrimitiveComponent* Component;
	FTransform Transform;

	FVaultComponentAndTransform(UPrimitiveComponent* Comp, FTransform Trans)
	{
		Component = Comp;
		Transform = Trans;
	}

	FVaultComponentAndTransform(): Component(nullptr)
	{
	}
};

struct VaultTraceSettings
{
	float MaxLedgeHeight;
	float MinLedgeHeight;
	float Distance;
	float ForwardTraceRadius;
	float DownwardTraceRadius;

	VaultTraceSettings() {}
	VaultTraceSettings(float MaxLH, float MinLH, float D, float FTR, float DTR)
	{
		MaxLedgeHeight = MaxLH;
		MinLedgeHeight = MinLH;
		Distance = D;
		ForwardTraceRadius = FTR;
		DownwardTraceRadius = DTR;
	}
};

USTRUCT(BlueprintType)
struct FVaultAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveVector* PositionCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartingOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LowHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LowPlayRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LowStartPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HightHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HightPlayRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HightStartPosition;

	FVaultAsset(): AnimMontage(nullptr), PositionCurve(nullptr), LowHeight(0), LowPlayRate(0), LowStartPosition(0),
	              HightHeight(0),
	              HightPlayRate(0),
	              HightStartPosition(0)
	{}
};

struct FVaultParams
{
	UAnimMontage* AnimMontage;
	UCurveVector* PositionCurve;
	FVector StartingOffset;
	float PlayRate;
	float StartingPosition;

	FVaultParams() : AnimMontage(nullptr), PositionCurve(nullptr), PlayRate(0), StartingPosition(0) {}

	FVaultParams(UAnimMontage* Anim, UCurveVector* Curve, float PlayR, float StartPos, FVector StartOffset)
	{
		AnimMontage = Anim;
		PositionCurve = Curve;
		PlayRate = PlayR;
		StartingPosition = StartPos;
		StartingOffset = StartOffset;
	}

	FVaultParams(FVaultAsset& VaultAsset, float PlayR, float StartPos)
	{
		AnimMontage = VaultAsset.AnimMontage;
		PositionCurve = VaultAsset.PositionCurve;
		PlayRate = PlayR;
		StartingPosition = StartPos;
		StartingOffset = VaultAsset.StartingOffset;
	}
};

UCLASS()
class PROJET_AARON_API AFPS_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPS_Character();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Climbing")
		float ClimbLerpSpeed = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Climbing")
		float ClimbRange = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HoldingTimeItemWheel = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RaycastDistanceInventory = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool CanVault = false;

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	template<EMovement EMovementCharacter>
	void MoveCharacter(float AxisValue);

	void StartJump();

	void Sprint();
	void StopSprint();

	void Crouching();
	void Dodge();

	void Action();
	void StopAction();
	void Scan();

	void ActivatePressedLeft();
	void ActivateReleasedLeft();

	void ActivatePressedRight();
	void ActivateReleasedRight();

	void ActivateHeadEquipment();
	
	void PressedItemWheel();
	void RepeatItemWheel();
	void ReleaseItemWheel();
	void DisplayWheel();

	bool VaultCheck(VaultTraceSettings TraceSettings);
	void VaultStart(float VaultHeight, FVaultComponentAndTransform VaultLedgeWS, VaultType VaultType);

	UFUNCTION(BlueprintCallable)
		FVector GetPlayerInput() const;

	UFUNCTION(BlueprintCallable)
		void UseMyItem(UDA_SlotStructure* ChosenSlot);
	void PressedUseQuickItem();

	UFUNCTION(BlueprintCallable)
		void ResetAdrenalineBoost();

	UFUNCTION()
		void UpdateTimelineFunction(float value);

	UFUNCTION()
		void EndTimelineFunction();

protected:

	FHitResult* HitGrab = nullptr;
	FHitResult* HitActor = nullptr;
	
	bool IsClimbing = false;
	bool IsLeftHandGripping = false;
	bool IsRightHandGripping = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Alignment;
	
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

	FVaultParams VaultParams;
	FVaultComponentAndTransform VaultLedgeLS;
	FTransform VaultStartOffset;
	FTransform VaultAnimatedStartOffset;

	FVector ClimbPosition = FVector::ZeroVector;
	FVector LeftHandPosition = FVector::ZeroVector;
	FVector RightHandPosition = FVector::ZeroVector;

	float CurrentTimePressedItemWheel = 0.f;
	bool WheelDisplayed = false;
	EStateMovement CurrentStateMovement;

	VaultTraceSettings GroundedTraceSettings = VaultTraceSettings(250.0f, 30.0f, 75.0f, 30.0f, 30.0f);
	VaultTraceSettings FallingTraceSettings = VaultTraceSettings(150.0f, 30.0f, 70.0f, 30.0f, 30.0f);
	
	virtual void BeginPlay() override;
	void CharacterClimb(float DeltaTime);
	void UpdateClimbingPosition();
	bool SearchClimbPoint(FVector& ClimbPoint);
	bool FindWallToClimb(VaultTraceSettings TraceSettings, FVector& InitialTraceImpactPoint, FVector& InitialTraceNormal);
	bool CanClimbOnWall(VaultTraceSettings TraceSettings, FVector& InitialTraceImpactPoint, FVector& InitialTraceNormal, float& VaultHeight, FVaultComponentAndTransform& TransformAndTransform, VaultType& Vault);
	bool CapsuleHasRoomCheck(FVector TargetLocation, float HeightOffset, float RadiusOffset);
	FVaultComponentAndTransform ConvertWorldToLocal(FVaultComponentAndTransform WorldSpaceVault);
	FVaultComponentAndTransform ConvertLocalToWorld(FVaultComponentAndTransform LocalSpaceVault);
	FVaultParams GetVaultParam(VaultType Vault, float VaultHeight);
	FTransform GetVaultStartOffset(FTransform& VaultTarget);
	FTransform GetVaultAnimatedStartOffset(FVaultParams& VaultParam ,FTransform& VaultTarget);
	FVector GetCapsuleBaseLocation(float ZOffset) const;
	FVector GetCapsuleBaseLocationFromBase(FVector BaseLocation ,float ZOffset) const;

	FOnTimelineFloat UpdateTimeline{};
	FOnTimelineEvent FinishTimeLine{};
};
