// Fill out your copyright notice in the Description page of Project Settings.

#include "UseEffect.h"
#include "GameFramework/Actor.h"
#include "InventoryComponent.h"

void UUseEffect::OnUse_Implementation(AActor* Instigator, UInventoryComponent* UsedInventory, int UsedSlotID, const FName& UsedItemID)
{

}

void UUseEffect::Execute(const TSubclassOf<UUseEffect>& Effect, AActor* Instigator, UInventoryComponent* UsedInventory, int UsedSlotID, const FName& UsedItemID)
{
    UUseEffect* Instance = NewObject<UUseEffect>(GetTransientPackage(), Effect);
    Instance->OnUse(Instigator, UsedInventory, UsedSlotID, UsedItemID);
}

void UUseEffect::ExecuteSequence(const TArray<TSubclassOf<UUseEffect>>& Effects, AActor* Instigator, UInventoryComponent* UsedInventory, int UsedSlotID, const FName& UsedItemID)
{
    for (const TSubclassOf<UUseEffect>& Effect : Effects)
    {
        Execute(Effect, Instigator, UsedInventory, UsedSlotID, UsedItemID);
    }
}