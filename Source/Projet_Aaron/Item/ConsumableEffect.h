// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemEffect.h"
#include "ConsumableEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UConsumableEffect : public UItemEffect
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		FName ItemAddedAfterUse;

	virtual void Execute(AActor* Instigator, UInventoryComponent* UsedInventory, int UsedSlotID, const FName& UsedItemID) override;
};
