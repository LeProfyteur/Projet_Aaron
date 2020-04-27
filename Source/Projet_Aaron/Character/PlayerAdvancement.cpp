// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAdvancement.h"
#include <Runtime\CoreUObject\Public\UObject\ConstructorHelpers.h>

// Sets default values for this component's properties
UPlayerAdvancement::UPlayerAdvancement()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerAdvancement::UnlockAbilities(FString EntryName)
{
	if (unlockableAbilities.Contains(EntryName))
		unlockableAbilities[EntryName] = true;
	else if (metroidvaniaAbilities.Contains(EntryName))
		metroidvaniaAbilities[EntryName] = true;
}

bool UPlayerAdvancement::IsUnlock(FString EntryName)
{
	if (scannableItems.Contains(EntryName))
		return scannableItems[EntryName];
	else if (collectableItems.Contains(EntryName))
		return collectableItems[EntryName];
	return false;
}

void UPlayerAdvancement::UnlockItem(FString EntryName)
{
	if (scannableItems.Contains(EntryName))
		scannableItems[EntryName] = true;
	else if (collectableItems.Contains(EntryName))
		collectableItems[EntryName] = true;
}

bool UPlayerAdvancement::GetScannableItemStatus(FString EntryName)
{
	if (scannableItems.Contains(EntryName)) 
		return scannableItems[EntryName];
	return false;
}

bool UPlayerAdvancement::GetUnlockableAbilities(FString EntryName)
{
	if (unlockableAbilities.Contains(EntryName)) 
		return unlockableAbilities[EntryName];
	return false;
}

bool UPlayerAdvancement::GetMetroidvaniaAbilities(FString EntryName)
{
	if (metroidvaniaAbilities.Contains(EntryName)) 
		return metroidvaniaAbilities[EntryName];
	return false;
}

bool UPlayerAdvancement::GetCollectableItems(FString EntryName)
{
	if (collectableItems.Contains(EntryName))
		return collectableItems[EntryName];
	return false;
}
