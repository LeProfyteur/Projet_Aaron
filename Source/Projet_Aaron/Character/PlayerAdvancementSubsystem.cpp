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
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancementSubsystem->unlockableAbilities.Contains(EntryName))
				PlayerAdvancementSubsystem->unlockableAbilities[EntryName] = true;
			else if (PlayerAdvancementSubsystem->metroidvaniaAbilities.Contains(EntryName))
				PlayerAdvancementSubsystem->metroidvaniaAbilities[EntryName] = true;
		}
	}
}

bool UPlayerAdvancementSubsystem::IsUnlock(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancementSubsystem->scannableItems.Contains(EntryName))
				return PlayerAdvancementSubsystem->scannableItems[EntryName];
			else if (PlayerAdvancementSubsystem->collectableItems.Contains(EntryName))
				return PlayerAdvancementSubsystem->collectableItems[EntryName];
		}
	}
	return false;
}

bool UPlayerAdvancementSubsystem::IsUnlockAbilities(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancementSubsystem->unlockableAbilities.Contains(EntryName))
				return PlayerAdvancementSubsystem->unlockableAbilities[EntryName];
			else if (PlayerAdvancementSubsystem->metroidvaniaAbilities.Contains(EntryName))
				return PlayerAdvancementSubsystem->metroidvaniaAbilities[EntryName];
		}
	}
	return false;
}

void UPlayerAdvancementSubsystem::UnlockItem(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancementSubsystem->scannableItems.Contains(EntryName))
				PlayerAdvancementSubsystem->scannableItems[EntryName] = true;
			else if (PlayerAdvancementSubsystem->collectableItems.Contains(EntryName))
				PlayerAdvancementSubsystem->collectableItems[EntryName] = true;
		}
	}
}

bool UPlayerAdvancementSubsystem::GetScannableItemStatus(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancementSubsystem->scannableItems.Contains(EntryName))
				return PlayerAdvancementSubsystem->scannableItems[EntryName];
		}
	}
	return false;
}

bool UPlayerAdvancementSubsystem::GetUnlockableAbilities(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancementSubsystem->unlockableAbilities.Contains(EntryName))
				return PlayerAdvancementSubsystem->unlockableAbilities[EntryName];
		}
	}
	return false;
}

bool UPlayerAdvancementSubsystem::GetMetroidvaniaAbilities(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancementSubsystem->metroidvaniaAbilities.Contains(EntryName))
				return PlayerAdvancementSubsystem->metroidvaniaAbilities[EntryName];
		}
	}
	return false;
}

bool UPlayerAdvancementSubsystem::GetCollectableItems(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancementSubsystem->collectableItems.Contains(EntryName))
				return PlayerAdvancementSubsystem->collectableItems[EntryName];
		}
	}
	return false;
}

bool UPlayerAdvancementSubsystem::GetItemCompletion(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancementSubsystem->collectableItemsCompleted.Contains(EntryName))
				return PlayerAdvancementSubsystem->collectableItemsCompleted[EntryName] ;
		}
	}
	return false;
}

void UPlayerAdvancementSubsystem::SetScannableItemStatus(FString EntryName, bool isScanned)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancementSubsystem->scannableItems.Contains(EntryName)) PlayerAdvancementSubsystem->scannableItems[EntryName] = isScanned;
		}
	}
}

void UPlayerAdvancementSubsystem::SetUnlockableAbilities(FString EntryName, bool isUnlocked)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancementSubsystem->unlockableAbilities.Contains(EntryName)) PlayerAdvancementSubsystem->unlockableAbilities[EntryName] = isUnlocked;
		}
	}
}
void UPlayerAdvancementSubsystem::SetMetroidvaniaAbilities(FString EntryName, bool isUnlocked)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancementSubsystem->metroidvaniaAbilities.Contains(EntryName)) PlayerAdvancementSubsystem->metroidvaniaAbilities[EntryName] = isUnlocked;
		}
	}
}
void UPlayerAdvancementSubsystem::SetCollectableItems(FString EntryName, bool isCollected)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancementSubsystem->collectableItems.Contains(EntryName)) PlayerAdvancementSubsystem->collectableItems[EntryName] = isCollected;
		}
	}
}

void UPlayerAdvancementSubsystem::SetItemCompletion(FString EntryName, bool isCompleted)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancementSubsystem->collectableItemsCompleted.Contains(EntryName)) PlayerAdvancementSubsystem->collectableItemsCompleted[EntryName] = isCompleted;
		}
	}
}

TArray<int32> UPlayerAdvancementSubsystem::GetSavedEquipmentSet(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancementSubsystem->savedEquipmentSets.Contains(EntryName)) 
				return PlayerAdvancementSubsystem->savedEquipmentSets[EntryName];
		}
	}
	return {-1,-1,-1,-1,-1,-1,-1-1,-1,-1};
}

void UPlayerAdvancementSubsystem::AddSavedEquipmentSet(FString EntryName, TArray<int32> equipmentIndexes)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (!PlayerAdvancementSubsystem->savedEquipmentSets.Contains(EntryName))
				PlayerAdvancementSubsystem->savedEquipmentSets.Add(EntryName,equipmentIndexes);
		}
	}
}

void UPlayerAdvancementSubsystem::RemoveSavedEquipmentSet(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			if (PlayerAdvancementSubsystem->savedEquipmentSets.Contains(EntryName))
				PlayerAdvancementSubsystem->savedEquipmentSets.Remove(EntryName);
		}
	}
}

TArray<FString> UPlayerAdvancementSubsystem::GetAllSavedEquipmentSet()
{
	TArray<FString> keysSavedEquipmentSets;
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			PlayerAdvancementSubsystem->savedEquipmentSets.GetKeys(keysSavedEquipmentSets);
		}
	}
	return keysSavedEquipmentSets;
}

void UPlayerAdvancementSubsystem::SetCanRecreateCharacter(bool Value)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			PlayerAdvancementSubsystem->CanRecreateCharacter = Value;
		}
	}
}

void UPlayerAdvancementSubsystem::SetTutorialCompleted(bool Value)
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			PlayerAdvancementSubsystem->TutorialCompleted = Value;
		}
	}
}

bool UPlayerAdvancementSubsystem::GetCanRecreateCharacter()
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			return PlayerAdvancementSubsystem->CanRecreateCharacter;
		}
	}
	return false;
}

bool UPlayerAdvancementSubsystem::GetTutorialCompleted()
{
	if (GEngine)
	{
		if (UPlayerAdvancementSubsystem* PlayerAdvancementSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancementSubsystem>())
		{
			return PlayerAdvancementSubsystem->TutorialCompleted;
		}
	}
	return false;
}
