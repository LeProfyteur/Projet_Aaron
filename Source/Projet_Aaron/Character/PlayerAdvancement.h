// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Subsystems/EngineSubsystem.h"
#include "PlayerAdvancement.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJET_AARON_API UPlayerAdvancement : public UEngineSubsystem
{
	GENERATED_BODY()

	TMap <FString, bool> scannableItems = { {"LightPlantScan",true}, {"PoisonPlantScan",false} ,{"BlockingPlantScan",false}  ,{"PuncturePlantScan",false} ,{"CarnivorousPlantScan",false} ,{"PakurvaScan",false},{"LumeilScan",false} ,{"KorvaifScan",false} ,{"GrosHerbivoreScan",false} };
	TMap <FString, bool> collectableItems = { {"ParalysingDartBlackBox",false}, {"GrapnelItem",false} ,{"WeakeningDartDocument",false},{"EnvironmentalScanBeacon",false},{"MovementDetectorBeacon",false}, {"GliderBlackBox",false}, {"PoweredBootsBlackBox",false}, {"GillsDoc",false}, {"NightVisionBlackBox",false}, {"TrackerBlackBox",false} };
	TMap <FString, bool> unlockableAbilities = { {"EnvironmentalScan",true}, {"MovementDetector",false} ,{"ParalysingDartGun",true} ,{"WeakeningDartGun",false} ,{"SoundImitation",false} ,{"OpticCamouflage",false} ,{"FertilizerGun",false},{"Hound",false},{"GrowingRoots",false},{"BarkCovering",false},{"Tracker",false},{"TimeSlow",false},{"Glider",false},{"PoweredBoots",false},{"EmpoweredDash",false},{"PheromonesRelease",false},{"Allergy",true},{"Hallucination",false},{"FastSwimming",false},{"BiologicalRegeneration",false},{"ToughSkin",false},{"HeartContractrion",false} };
	TMap <FString, bool> metroidvaniaAbilities = { {"NightVision",false}, {"Grapnel",false} ,{"Gills",false},{"ExtremeTemperaturesResistance",false},{"StickyFeet",false} };



public:
	// Sets default values for this component's properties

	UFUNCTION(BlueprintCallable)
		void ResetAdvancement();

	UFUNCTION(BlueprintCallable)
		static void UnlockAbilities(FString EntryName);

	UFUNCTION(BlueprintCallable)
		static bool IsUnlock(FString EntryName);

	UFUNCTION(BlueprintCallable)
		static bool IsUnlockAbilities(FString EntryName);

	UFUNCTION(BlueprintCallable)
		static void UnlockItem(FString EntryName);

public:
	UFUNCTION(BlueprintCallable)
		static void SetScannableItemStatus(FString EntryName, bool isScanned);

	UFUNCTION(BlueprintCallable)
		static void SetUnlockableAbilities(FString EntryName, bool isUnlocked);

	UFUNCTION(BlueprintCallable)
		static void SetMetroidvaniaAbilities(FString EntryName, bool isUnlocked);

	UFUNCTION(BlueprintCallable)
		static void SetCollectableItems(FString EntryName, bool isCollected);

public:
	UFUNCTION(BlueprintCallable)
		static bool GetScannableItemStatus(FString EntryName);

	UFUNCTION(BlueprintCallable)
		static bool GetUnlockableAbilities(FString EntryName);

	UFUNCTION(BlueprintCallable)
		static bool GetMetroidvaniaAbilities(FString EntryName);

	UFUNCTION(BlueprintCallable)
		static bool GetCollectableItems(FString EntryName);


};
