// Fill out your copyright notice in the Description page of Project Settings.


#include "InventaireComponentBase.h"

UInventaireBaseComponent::UInventaireBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventaireBaseComponent::PrepareInventory()
{
	NumberOfSlots = 8;
	Inventory.Reserve(NumberOfSlots);
	InventoryConsomable.Reserve(NumberOfSlots);
	InventoryFlacon.Reserve(NumberOfSlots);
	InventoryName = "Base";
}

int UInventaireBaseComponent::GetIndexSlot(UDA_ItemStructure* ItemToSearch)
{

	for (int i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i]->ItemStructure->Name == ItemToSearch->Name)
		{
			return i;
		}
	}
	return -1;
}

int UInventaireBaseComponent::GetIndexSlotConso(UDA_ItemStructure* ItemToSearch)
{
	for (int i = 0; i < InventoryConsomable.Num(); i++)
	{
		//UE_LOG(LogActor, Warning, TEXT("Item search : %d"), InventoryConsomable[i]->Quantity);
		if (InventoryConsomable[i]->ItemStructure->Name == ItemToSearch->Name)
		{
			return i;
		}
	}
	return -1;
}

int UInventaireBaseComponent::GetIndexSlotSeringue(UDA_ItemStructure* ItemToSearch)
{
	for (int i = 0; i < InventoryFlacon.Num(); i++)
	{
		//UE_LOG(LogActor, Warning, TEXT("Item search : %d"), InventoryFlacon[i]->Quantity);
		if (InventoryFlacon[i]->ItemStructure->Name == ItemToSearch->Name)
		{
			return i;
		}
	}
	return -1;
}
