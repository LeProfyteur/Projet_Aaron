// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UseEffect.generated.h"

UCLASS(Blueprintable)
class PROJET_AARON_API UUseEffect : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnUse(class AActor* Instigator, class UInventoryComponent* UsedInventory, int UsedSlotID, const FName& UsedItemID);
	virtual void OnUse_Implementation(class AActor* Instigator, class UInventoryComponent* UsedInventory, int UsedSlotID, const FName& UsedItemID);

	UFUNCTION(BlueprintCallable)
		static void Execute(const TSubclassOf<UUseEffect>& Effect, class AActor* Instigator, class UInventoryComponent* UsedInventory, int UsedSlotID, const FName& UsedItemID);

	UFUNCTION(BlueprintCallable)
		static void ExecuteSequence(const TArray<TSubclassOf<UUseEffect>>& Effects, class AActor* Instigator, class UInventoryComponent* UsedInventory, int UsedSlotID, const FName& UsedItemID);
};