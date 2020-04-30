// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAdvancementSubsystem.h"
#include "Engine/Engine.h"

void UPlayerAdvancementSubsystem::ResetAdvancement()
{
	scannableItems = { {"LightPlantScan",false}, {"PoisonPlantScan",false} ,{"BlockingPlantScan",false}  ,{"PuncturePlantScan",false} ,{"CarnivorousPlantScan",false} ,{"PakurvaScan",false},{"LumeilScan",false} ,{"KorvaifScan",false} ,{"GrosHerbivoreScan",false} };
	collectableItems = { {"ParalysingDartBlackBox",false}, {"GrapnelItem",false} ,{"WeakeningDartDocument",false},{"EnvironmentalScanBeacon",false},{"MovementDetectorBeacon",false}, {"GliderBlackBox",false}, {"PoweredBootsBlackBox",false}, {"GillsDoc",false}, {"NightVisionBlackBox",false}, {"TrackerBlackBox",false} };
	unlockableAbilities = { {"EnvironmentalScan",false}, {"MovementDetector",false} ,{"ParalysingDartGun",false} ,{"WeakeningDartGun",false} ,{"SoundImitation",false} ,{"OpticCamouflage",false} ,{"FertilizerGun",false},{"Hound",false},{"GrowingRoots",false},{"BarkCovering",false},{"Tracker",false},{"TimeSlow",false},{"Glider",false},{"PoweredBoots",false},{"EmpoweredDash",false},{"PheromonesRelease",false},{"Allergy",false},{"Hallucination",false},{"FastSwimming",false},{"BiologicalRegeneration",false},{"ToughSkin",false},{"HeartContractrion",false} };
	metroidvaniaAbilities = { {"NightVision",false}, {"Grapnel",false} ,{"Gills",false},{"ExtremeTemperaturesResistance",false},{"StickyFeet",false} };
	collectableItemsCompleted = { {"ParalysingDartBlackBox",false}, {"GrapnelItem",false} ,{"WeakeningDartDocument",false},{"EnvironmentalScanBeacon",false},{"MovementDetectorBeacon",false}, {"GliderBlackBox",false}, {"PoweredBootsBlackBox",false}, {"GillsDoc",false}, {"NightVisionBlackBox",false}, {"TrackerBlackBox",false} };
	savedEquipmentSets.Reset();
}

void UPlayerAdvancementSubsystem::UnlockAbilities(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancemntSubsystem->unlockableAbilities.Contains(EntryName))
				PlayerAdvancemntSubsystem->unlockableAbilities[EntryName] = true;
			else if (PlayerAdvancemntSubsystem->metroidvaniaAbilities.Contains(EntryName))
				PlayerAdvancemntSubsystem->metroidvaniaAbilities[EntryName] = true;
		}
	}
}

bool UPlayerAdvancementSubsystem::IsUnlock(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancemntSubsystem->scannableItems.Contains(EntryName))
				return PlayerAdvancemntSubsystem->scannableItems[EntryName];
			else if (PlayerAdvancemntSubsystem->collectableItems.Contains(EntryName))
				return PlayerAdvancemntSubsystem->collectableItems[EntryName];
		}
	}
	return false;
}

bool UPlayerAdvancementSubsystem::IsUnlockAbilities(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancemntSubsystem->unlockableAbilities.Contains(EntryName))
				return PlayerAdvancemntSubsystem->unlockableAbilities[EntryName];
			else if (PlayerAdvancemntSubsystem->metroidvaniaAbilities.Contains(EntryName))
				return PlayerAdvancemntSubsystem->metroidvaniaAbilities[EntryName];
		}
	}
	return false;
}

void UPlayerAdvancementSubsystem::UnlockItem(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancemntSubsystem->scannableItems.Contains(EntryName))
				PlayerAdvancemntSubsystem->scannableItems[EntryName] = true;
			else if (PlayerAdvancemntSubsystem->collectableItems.Contains(EntryName))
				PlayerAdvancemntSubsystem->collectableItems[EntryName] = true;
		}
	}
}

bool UPlayerAdvancementSubsystem::GetScannableItemStatus(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancemntSubsystem->scannableItems.Contains(EntryName))
				return PlayerAdvancemntSubsystem->scannableItems[EntryName];
		}
	}
	return false;
}

bool UPlayerAdvancementSubsystem::GetUnlockableAbilities(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancemntSubsystem->unlockableAbilities.Contains(EntryName))
				return PlayerAdvancemntSubsystem->unlockableAbilities[EntryName];
		}
	}
	return false;
}

bool UPlayerAdvancementSubsystem::GetMetroidvaniaAbilities(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancemntSubsystem->metroidvaniaAbilities.Contains(EntryName))
				return PlayerAdvancemntSubsystem->metroidvaniaAbilities[EntryName];
		}
	}
	return false;
}

bool UPlayerAdvancementSubsystem::GetCollectableItems(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancemntSubsystem->collectableItems.Contains(EntryName))
				return PlayerAdvancemntSubsystem->collectableItems[EntryName];
		}
	}
	return false;
}

bool UPlayerAdvancementSubsystem::GetItemCompletion(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancemntSubsystem->collectableItemsCompleted.Contains(EntryName))
				return PlayerAdvancemntSubsystem->collectableItemsCompleted[EntryName] ;
		}
	}
	return false;
}

void UPlayerAdvancementSubsystem::SetScannableItemStatus(FString EntryName, bool isScanned)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancemntSubsystem->scannableItems.Contains(EntryName)) PlayerAdvancemntSubsystem->scannableItems[EntryName] = isScanned;
		}
	}
}

void UPlayerAdvancementSubsystem::SetUnlockableAbilities(FString EntryName, bool isUnlocked)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancemntSubsystem->unlockableAbilities.Contains(EntryName)) PlayerAdvancemntSubsystem->unlockableAbilities[EntryName] = isUnlocked;
		}
	}
}
void UPlayerAdvancementSubsystem::SetMetroidvaniaAbilities(FString EntryName, bool isUnlocked)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancemntSubsystem->metroidvaniaAbilities.Contains(EntryName)) PlayerAdvancemntSubsystem->metroidvaniaAbilities[EntryName] = isUnlocked;
		}
	}
}
void UPlayerAdvancementSubsystem::SetCollectableItems(FString EntryName, bool isCollected)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancemntSubsystem->collectableItems.Contains(EntryName)) PlayerAdvancemntSubsystem->collectableItems[EntryName] = isCollected;
		}
	}
}

void UPlayerAdvancementSubsystem::SetItemCompletion(FString EntryName, bool isCompleted)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancemntSubsystem->collectableItemsCompleted.Contains(EntryName)) PlayerAdvancemntSubsystem->collectableItemsCompleted[EntryName] = isCompleted;
		}
	}
}

TArray<int32> UPlayerAdvancementSubsystem::GetSavedEquipmentSet(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancemntSubsystem->savedEquipmentSets.Contains(EntryName)) 
				return PlayerAdvancemntSubsystem->savedEquipmentSets[EntryName];
		}
	}
	return {-1,-1,-1,-1,-1,-1,-1-1,-1,-1};
}

void UPlayerAdvancementSubsystem::AddSavedEquipmentSet(FString EntryName, TArray<int32> equipmentIndexes)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (!PlayerAdvancemntSubsystem->savedEquipmentSets.Contains(EntryName))
				PlayerAdvancemntSubsystem->savedEquipmentSets.Add(EntryName,equipmentIndexes);
		}
	}
}

void UPlayerAdvancementSubsystem::RemoveSavedEquipmentSet(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancemntSubsystem->savedEquipmentSets.Contains(EntryName))
				PlayerAdvancemntSubsystem->savedEquipmentSets.Remove(EntryName);
		}
	}
}

TArray<FString> UPlayerAdvancementSubsystem::GetAllSavedEquipmentSet()
{
	TArray<FString> keysSavedEquipmentSets;
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			PlayerAdvancemntSubsystem->savedEquipmentSets.GetKeys(keysSavedEquipmentSets);
		}
	}
	return keysSavedEquipmentSets;
}
