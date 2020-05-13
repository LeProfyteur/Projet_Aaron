// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Projet_Aaron/Character/CharacterUtils.h"
#include "Subsystems/EngineSubsystem.h"
#include "PlayerAdvancementSubsystem.generated.h"


UCLASS()
class PROJET_AARON_API UPlayerAdvancementSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	TMap <FString, bool> scannableItems;
	TMap <FString, bool> collectableItems;
	TMap <FString, bool> unlockableAbilities;
	TMap <FString, bool> metroidvaniaAbilities;
	TMap <FString, bool> collectableItemsCompleted;
	TMap <FString, TArray<int32>> savedEquipmentSets;

protected:
	bool CanRecreateCharacter = false;
	bool TutorialCompleted = false;


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

	UFUNCTION(BlueprintCallable)
		static void CheckUnlockAbilities(FString EntryName);

public:
	UFUNCTION(BlueprintCallable)
		static void SetScannableItemStatus(FString EntryName, bool isScanned);

	UFUNCTION(BlueprintCallable)
		static void SetUnlockableAbilities(FString EntryName, bool isUnlocked);

	UFUNCTION(BlueprintCallable)
		static void SetMetroidvaniaAbilities(FString EntryName, bool isUnlocked);

	UFUNCTION(BlueprintCallable)
		static void SetCollectableItems(FString EntryName, bool isCollected);

	UFUNCTION(BlueprintCallable)
		static void SetItemCompletion(FString EntryName, bool isCompleted);

	UFUNCTION(BlueprintCallable)
		static void AddSavedEquipmentSet(FString EntryName, TArray<int32> equipmentIndexes);
	
	UFUNCTION(BlueprintCallable)
		static void RemoveSavedEquipmentSet(FString EntryName);

	UFUNCTION(BlueprintCallable)
		static void SetCanRecreateCharacter(bool Value);

	UFUNCTION(BlueprintCallable)
		static void SetTutorialCompleted(bool Value);

public:
	UFUNCTION(BlueprintCallable)
		static bool GetScannableItemStatus(FString EntryName);

	UFUNCTION(BlueprintCallable)
		static bool GetUnlockableAbilities(FString EntryName);

	UFUNCTION(BlueprintCallable)
		static bool GetMetroidvaniaAbilities(FString EntryName);

	UFUNCTION(BlueprintCallable)
		static bool GetCollectableItems(FString EntryName);

	UFUNCTION(BlueprintCallable)
		static bool GetItemCompletion(FString EntryName);

	UFUNCTION(BlueprintCallable)
		static TArray<int32> GetSavedEquipmentSet(FString EntryName);

	UFUNCTION(BlueprintCallable)
		static TArray<FString> GetAllSavedEquipmentSet();

	UFUNCTION(BlueprintCallable)
		static bool GetCanRecreateCharacter();

	UFUNCTION(BlueprintCallable)
		static bool GetTutorialCompleted();
};
