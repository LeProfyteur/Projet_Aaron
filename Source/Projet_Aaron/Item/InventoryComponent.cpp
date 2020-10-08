// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
    Slots.SetNum(4);
}

bool UInventoryComponent::IsSlotEmpty(int SlotID)
{
    return Slots.IsValidIndex(SlotID) || Slots[SlotID] == NAME_None;
}

FName UInventoryComponent::GetItem(int SlotID)
{
    return Slots.IsValidIndex(SlotID) ? Slots[SlotID] : NAME_None;
}

void UInventoryComponent::SetItem(int SlotID, FName ItemID)
{
    if (Slots.IsValidIndex(SlotID))
    {
        Slots[SlotID] = ItemID;
        OnInventorySlotChanged.Broadcast(SlotID, ItemID);
    }
}

bool UInventoryComponent::AddItem(FName ItemID)
{
    for (int SlotID = 0; SlotID < Slots.Num(); ++SlotID)
    {
        if (IsSlotEmpty(SlotID))
        {
            SetItem(SlotID, ItemID);
            return true;
        }
    }
    return true;
}

bool UInventoryComponent::RemoveItem(FName ItemID)
{
    for (int SlotID = 0; SlotID < Slots.Num(); ++SlotID)
    {
        if (GetItem(SlotID) == ItemID)
        {
            SetItem(SlotID, NAME_None);
            return true;
        }
    }
    return false;
}

bool UInventoryComponent::FindItem(FName ItemID, int& OutSlotID)
{
    for (int SlotID = 0; SlotID < Slots.Num(); ++SlotID)
    {
        if (GetItem(SlotID) == ItemID)
        {
            OutSlotID = SlotID;
            return true;
        }
    }
    return false;
}
