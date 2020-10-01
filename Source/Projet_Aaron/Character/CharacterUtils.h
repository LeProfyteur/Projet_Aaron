// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveVector.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "Animation/AnimMontage.h"
#include "CharacterUtils.generated.h"

/**
 * 
 */
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

UENUM(BlueprintType)
enum class EEquipment : uint8
{
	Metroidvania,
	Arm,
	Head,
	Torso,
	Legs,
	Abilities
};

USTRUCT(BlueprintType)
struct FCharacterSkills
{
	GENERATED_BODY()

public:
	bool SuperJump;
	bool Glider;
	bool Gills;
	bool MagnetBoots;
	bool NightVision;
	bool Pheromone;
	UPROPERTY(BlueprintReadWrite)
	bool Allergy;
	bool Hallucination;
	bool BioRegeneration;
	bool CocotteMinute;
	bool HardBark;
	bool Stilt;

	FCharacterSkills()
	{
		SuperJump = false;
		Glider = false;
		Gills = false;
		MagnetBoots = false;
		NightVision = false;
		Pheromone = false;
		Allergy = false;
		Hallucination = false;
		BioRegeneration = false;
		CocotteMinute = false;
		HardBark = false;
		Stilt = false;
	}
};

USTRUCT(BlueprintType)
struct FAbilitiesRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	FAbilitiesRow() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEquipment CategoryEquipment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Thumbnail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
		UClass *Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> UnlockRequirement;
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

	FVaultComponentAndTransform() : Component(nullptr)
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

	FVaultAsset() : AnimMontage(nullptr), PositionCurve(nullptr), LowHeight(0), LowPlayRate(0), LowStartPosition(0),
		HightHeight(0),
		HightPlayRate(0),
		HightStartPosition(0)
	{}

	GENERATED_BODY()
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

class PROJET_AARON_API CharacterUtils
{
public:
	CharacterUtils();
	~CharacterUtils();
};
