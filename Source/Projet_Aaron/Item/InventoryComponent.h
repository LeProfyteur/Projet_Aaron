// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInventorySlotChangedEvent, int, SlotID, FName, ItemID);

UCLASS( meta=(BlueprintSpawnableComponent) )
class PROJET_AARON_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();
	
	UFUNCTION(BlueprintCallable)
		bool IsSlotEmpty(int SlotID);

	UFUNCTION(BlueprintCallable)
        FName GetItem(int SlotID);

	UFUNCTION(BlueprintCallable)
        void SetItem(int SlotID, FName ItemID);

    UFUNCTION(BlueprintCallable)
        bool AddItem(FName ItemID);

    UFUNCTION(BlueprintCallable)
        bool RemoveItem(FName ItemID);

    UFUNCTION(BlueprintCallable)
        bool FindItem(FName ItemID, int& OutSlotID);

protected:
	UPROPERTY(BlueprintAssignable)
		FInventorySlotChangedEvent OnInventorySlotChanged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
        TArray<FName> Slots;
		
private:
};