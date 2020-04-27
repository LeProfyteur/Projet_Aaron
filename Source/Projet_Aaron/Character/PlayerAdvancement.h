// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "PlayerAdvancement.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJET_AARON_API UPlayerAdvancement : public UActorComponent
{
	GENERATED_BODY()

	TMap <FString, bool> scannableItems = { {"LightPlant",false}, {"PoisonPlant",false} ,{"BlockingPlant",false} ,{"LumeilScan",false} ,{"PuncturePlantScan",false} ,{"CarnivorousPlantScan",false} ,{"PakuraScan",false} };
	TMap <FString, bool> collectableItems{ {"ParalysingDartBlackBox",false}, {"GrapnelItem",false} ,{"WeakeningDartDocument",false},{"EnvironmentalScanBeacon",false},{"MovementDetectorBeacon",false}, {"GliderBlackBox",false}, {"PoweredBootsBlackBox",false}, {"GillsDoc",false}, {"NightVisionBlackBox",false}, {"TrackerBlackBox",false} };
	TMap <FString, bool> unlockableAbilities = { {"EnvironmentalScan",false}, {"MovementDetector",false} ,{"ParalysingDartGun",true} ,{"WeakeningDartGun",false} ,{"SoundImitation",false} ,{"OpticCamouflage",false} ,{"FertilizerGun",false},{"Hound",false},{"GrowingRoots",false},{"BarkCovering",false},{"Tracker",false},{"TimeSlow",false},{"Glider",false},{"PoweredBoots",false},{"EmpoweredDash",false},{"PheromonesRelease",false},{"Allergy",true},{"Hallucination",false},{"FastSwimming",false},{"BiologicalRegeneration",false},{"ToughSkin",false},{"HeartContractrion",false} };
	TMap <FString, bool> metroidvaniaAbilities{ {"NightVision",false}, {"Grapnel",false} ,{"Gills",false},{"ExtremeTemperaturesResistance",false},{"StickyFeet",false} };

public:
	// Sets default values for this component's properties
	UPlayerAdvancement();

	UFUNCTION(BlueprintCallable)
		void UnlockAbilities(FString EntryName);

	UFUNCTION(BlueprintCallable)
		bool IsUnlock(FString EntryName);

	UFUNCTION(BlueprintCallable)
		void UnlockItem(FString EntryName);

public:
	UFUNCTION(BlueprintCallable)
		void SetScannableItemStatus(FString EntryName, bool isScanned) { if (scannableItems.Contains(EntryName)) scannableItems[EntryName] = isScanned; }

	UFUNCTION(BlueprintCallable)
		void SetUnlockableAbilities(FString EntryName, bool isUnlocked) { if (unlockableAbilities.Contains(EntryName)) unlockableAbilities[EntryName] = isUnlocked; }

	UFUNCTION(BlueprintCallable)
		void SetMetroidvaniaAbilities(FString EntryName, bool isUnlocked) { if (metroidvaniaAbilities.Contains(EntryName)) metroidvaniaAbilities[EntryName] = isUnlocked; }

	UFUNCTION(BlueprintCallable)
		void SetCollectableItems(FString EntryName, bool isCollected) { if (collectableItems.Contains(EntryName)) collectableItems[EntryName] = isCollected; }

public:
	UFUNCTION(BlueprintCallable)
		bool GetScannableItemStatus(FString EntryName);

	UFUNCTION(BlueprintCallable)
		bool GetUnlockableAbilities(FString EntryName);

	UFUNCTION(BlueprintCallable)
		bool GetMetroidvaniaAbilities(FString EntryName);

	UFUNCTION(BlueprintCallable)
		bool GetCollectableItems(FString EntryName);
};
