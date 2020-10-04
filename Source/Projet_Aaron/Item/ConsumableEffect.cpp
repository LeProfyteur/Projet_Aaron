// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableEffect.h"
#include "InventoryComponent.h"

void UConsumableEffect::Execute(AActor* Instigator, UInventoryComponent* UsedInventory, int UsedSlotID, const FName& UsedItemID)
{
	Super::Execute(Instigator, UsedInventory, UsedSlotID, UsedItemID);

	//Consume Mechanic
	UsedInventory->RemoveItem(UsedItemID);
	if (!ItemAddedAfterUse.IsNone())
	{
		UsedInventory->AddItem(ItemAddedAfterUse);
	}
}