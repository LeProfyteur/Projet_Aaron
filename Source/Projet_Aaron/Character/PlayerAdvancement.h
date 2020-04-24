// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerAdvancement.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJET_AARON_API UPlayerAdvancement : public UActorComponent
{
	GENERATED_BODY()

	TMap <FString, bool> scannableItems = { {"LightPlant",false}, {"PoisonPlant",false} ,{"BlockingPlant",false} ,{"Creature1",false} ,{"Creature2",false} ,{"Creature3",false} ,{"Creature4",false} };
	TMap <FString, bool> unlockableAbilities = { {"EnvironmentalScan",false}, {"MovementDetector",false} ,{"BlockPlant",false} ,{"Creature1",false} ,{"Creature2",false} ,{"Creature3",false} ,{"Creature4",false} };
	TMap <FString, bool> metroidvaniaAbilities{ {"NightVision",false}, {"Grapnel",false} ,{"Gills",false}};

public:
	// Sets default values for this component's properties
	UPlayerAdvancement();

protected:

public:

public:
	UFUNCTION(BlueprintCallable)
		void SetScannableItemStatus(FString entryName, bool isScanned) { scannableItems[entryName] = isScanned; }

	UFUNCTION(BlueprintCallable)
		void SetUnlockableAbilities(FString entryName, bool isUnlocked) { unlockableAbilities[entryName] = isUnlocked; }

	UFUNCTION(BlueprintCallable)
		void SetMetroidvaniaAbilities(FString entryName, bool isUnlocked) { metroidvaniaAbilities[entryName] = isUnlocked; }

public:
	UFUNCTION(BlueprintCallable)
		bool GetScannableItemStatus(FString entryName) { return scannableItems[entryName]; }

	UFUNCTION(BlueprintCallable)
		bool GetUnlockableAbilities(FString entryName) { return unlockableAbilities[entryName]; }

	UFUNCTION(BlueprintCallable)
		bool GetMetroidvaniaAbilities(FString entryName) { return metroidvaniaAbilities[entryName]; }
};
