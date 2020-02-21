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
		if(slot->ItemStructure->Category==ECategoryEnum::CE_Consomable)
		{
			if(InventoryConsomable.Num()>=3)
			{
				UE_LOG(LogActor, Error, TEXT("Already 3 slot taken in inventoryConsomable"));
			}else
			{
				InventoryConsomable.Add(slot);
			}
		}else if (slot->ItemStructure->Category == ECategoryEnum::CE_Seringue)
		{
			if(InventoryFlacon.Num()>=3)
			{
				UE_LOG(LogActor, Error, TEXT("Already 3 slot taken in InventorySeringue"));
			}else
			{
				InventoryFlacon.Add(slot);
			}
		}
		UE_LOG(LogActor, Warning, TEXT("Size inventory Conso : %d"), InventoryConsomable.Num());
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

			if (slot->ItemStructure->Category == ECategoryEnum::CE_Consomable)
			{
				if (InventoryConsomable.Num() >= 3)
				{
					UE_LOG(LogActor, Error, TEXT("Already 3 slot taken in inventoryConsomable"));
				}
				else
				{
					InventoryConsomable.Add(slot);
				}
			}
			else if (slot->ItemStructure->Category == ECategoryEnum::CE_Seringue)
			{
				if (InventoryFlacon.Num() >= 3)
				{
					UE_LOG(LogActor, Error, TEXT("Already 3 slot taken in InventorySeringue"));
				}
				else
				{
					InventoryFlacon.Add(slot);
				}
			}
		}
		else
		{
			UDA_SlotStructure* slot = Inventory[index];
			slot->Quantity++;

			//recherche sur les slot pour InventoryFacon et InventoryConso

			if (slot->ItemStructure->Category == ECategoryEnum::CE_Consomable)
			{
				int indexConso = GetIndexSlotConso(ItemToAdd);
				if (indexConso >= 0 && InventoryConsomable[indexConso]->Quantity< InventoryConsomable[indexConso]->ItemStructure->MaxStackSize)
				{
					UDA_SlotStructure* slotConso = InventoryConsomable[indexConso];
					//slotConso->Quantity++;
				}
				else
				{
					UE_LOG(LogActor, Error, TEXT("Already 3 stack full in InventoryConso"));

				}
			}
			else if (slot->ItemStructure->Category == ECategoryEnum::CE_Seringue)
			{
				int indexSeringue = GetIndexSlotSeringue(ItemToAdd);
				if (indexSeringue >= 0 && InventoryFlacon[indexSeringue]->Quantity < InventoryFlacon[indexSeringue]->ItemStructure->MaxStackSize)
				{
					UDA_SlotStructure* slotSeringue = InventoryFlacon[indexSeringue];
					//slotSeringue->Quantity++;
				}
				else
				{
					UE_LOG(LogActor, Error, TEXT("Already 3 stack full in InventorySeringue"));

				}
			}
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
			break;
		}
	}
	InventoryConsomable.RemoveSingle(SlotToRemove);
	for (int i = 0; i < InventoryConsomable.Num(); i++)
	{
		if(InventoryConsomable[i]->ItemStructure->Name == SlotToRemove->ItemStructure->Name && InventoryConsomable[i]->Quantity == SlotToRemove->Quantity)
		{
			InventoryConsomable.RemoveAt(i);
			break;
		}
	}

	for (int i = 0; i < InventoryFlacon.Num(); i++)
	{
		if (InventoryFlacon[i]->ItemStructure->Name == SlotToRemove->ItemStructure->Name && InventoryFlacon[i]->Quantity == SlotToRemove->Quantity)
		{
			InventoryFlacon.RemoveAt(i);
			break;
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

int UInventaireComponent::GetIndexSlotConso(UDA_ItemStructure* ItemToSearch)
{
	UE_LOG(LogActor, Warning, TEXT("Size Inventory : %d"), InventoryConsomable.Num());

	for (int i = 0; i < InventoryConsomable.Num(); i++)
	{
		UE_LOG(LogActor, Warning, TEXT("Item search : %d"), InventoryConsomable[i]->Quantity);
		if (InventoryConsomable[i]->ItemStructure->Name == ItemToSearch->Name && InventoryConsomable[i]->ItemStructure->MaxStackSize > InventoryConsomable[i]->Quantity)
		{
			UE_LOG(LogActor, Warning, TEXT("Item trouvé : %p"), InventoryConsomable[i]);
			return i;
		}
	}
	return -1;
}

int UInventaireComponent::GetIndexSlotSeringue(UDA_ItemStructure* ItemToSearch)
{
	UE_LOG(LogActor, Warning, TEXT("Size Inventory : %d"), InventoryFlacon.Num());

	for (int i = 0; i < InventoryFlacon.Num(); i++)
	{
		UE_LOG(LogActor, Warning, TEXT("Item search : %d"), InventoryFlacon[i]->Quantity);
		if (InventoryFlacon[i]->ItemStructure->Name == ItemToSearch->Name && InventoryFlacon[i]->ItemStructure->MaxStackSize > InventoryFlacon[i]->Quantity)
		{
			UE_LOG(LogActor, Warning, TEXT("Item trouvé : %p"), InventoryFlacon[i]);
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

