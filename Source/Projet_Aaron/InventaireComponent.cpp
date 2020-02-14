// Fill out your copyright notice in the Description page of Project Settings.


#include "InventaireComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UInventaireComponent::UInventaireComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventaireComponent::AddToInventory(UDA_ItemStructure* ItemToAdd)
{

	if (!ItemToAdd->IsStackable)
	{
		//UDA_SlotStructure slot = new UDA_SlotStructure();
		//UDA_SlotStructure slot = UDA_SlotStructure(FObjectInitializer::Get());
		UDA_SlotStructure* slot = NewObject<UDA_SlotStructure>();
		//UDA_SlotStructure slot;
		slot->ItemStructure = ItemToAdd;
		slot->Quantity = 1;
		UE_LOG(LogActor, Warning, TEXT("Pickup nom : %s"), *slot->ItemStructure->Name);
		Inventory.Add(slot);
		//Inventory.Insert(slot, 0);
	}
	else
	{
		int index = GetIndexSlot(ItemToAdd);
		UE_LOG(LogActor, Warning, TEXT("Index : %d"), index);

		if (index < 0)
		{
			UDA_SlotStructure* slot = NewObject<UDA_SlotStructure>();
			slot->ItemStructure = ItemToAdd;
			slot->Quantity = 1;
			Inventory.Add(slot);
		}
		else
		{
			UDA_SlotStructure* slot = Inventory[index];
			slot->Quantity++;
		}
	}

	//Inventory.Add(ItemToAdd);
}

void UInventaireComponent::RemoveFromInventory(UDA_SlotStructure* SlotToRemove)
{
	for (int i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i]->ItemStructure->Name == SlotToRemove->ItemStructure->Name && Inventory[i]->Quantity == SlotToRemove->Quantity)
		{
			//index found
			Inventory.RemoveAt(i);
			return;
		}
	}
}

void UInventaireComponent::PrepareInventory()
{
	Inventory.Reserve(NumberOfSlots);
	UE_LOG(LogActor, Warning, TEXT("InventorySetup"));
}

int UInventaireComponent::GetIndexSlot(UDA_ItemStructure* ItemToSearch)
{
	// index = -1;
	UE_LOG(LogActor, Warning, TEXT("Size Inventory : %d"), Inventory.Num());

	for (int i = 0; i < Inventory.Num(); i++)
	{
		UE_LOG(LogActor, Warning, TEXT("Item search : %d"), Inventory[i]->Quantity);
		if (Inventory[i]->ItemStructure->Name == ItemToSearch->Name && Inventory[i]->ItemStructure->MaxStackSize > Inventory[i]->Quantity)
		{
			UE_LOG(LogActor, Warning, TEXT("Item trouvé : %p"), Inventory[i]);
			return i;
		}
	}
	return -1;
}

// Called when the game starts
void UInventaireComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UInventaireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

