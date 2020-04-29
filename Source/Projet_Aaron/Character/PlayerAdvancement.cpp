// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAdvancement.h"
#include "Engine/Engine.h"

void UPlayerAdvancement::ResetAdvancement()
{
	scannableItems = { {"LightPlantScan",false}, {"PoisonPlantScan",false} ,{"BlockingPlantScan",false}  ,{"PuncturePlantScan",false} ,{"CarnivorousPlantScan",false} ,{"PakurvaScan",false},{"LumeilScan",false} ,{"KorvaifScan",false} ,{"GrosHerbivoreScan",false} };
	collectableItems={ {"ParalysingDartBlackBox",false}, {"GrapnelItem",false} ,{"WeakeningDartDocument",false},{"EnvironmentalScanBeacon",false},{"MovementDetectorBeacon",false}, {"GliderBlackBox",false}, {"PoweredBootsBlackBox",false}, {"GillsDoc",false}, {"NightVisionBlackBox",false}, {"TrackerBlackBox",false} };
	unlockableAbilities = { {"EnvironmentalScan",false}, {"MovementDetector",false} ,{"ParalysingDartGun",false} ,{"WeakeningDartGun",false} ,{"SoundImitation",false} ,{"OpticCamouflage",false} ,{"FertilizerGun",false},{"Hound",false},{"GrowingRoots",false},{"BarkCovering",false},{"Tracker",false},{"TimeSlow",false},{"Glider",false},{"PoweredBoots",false},{"EmpoweredDash",false},{"PheromonesRelease",false},{"Allergy",false},{"Hallucination",false},{"FastSwimming",false},{"BiologicalRegeneration",false},{"ToughSkin",false},{"HeartContractrion",false} };
	metroidvaniaAbilities={ {"NightVision",false}, {"Grapnel",false} ,{"Gills",false},{"ExtremeTemperaturesResistance",false},{"StickyFeet",false} };
}

void UPlayerAdvancement::UnlockAbilities(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancement* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancement>())
		{
			if (PlayerAdvancemntSubsystem->unlockableAbilities.Contains(EntryName))
				PlayerAdvancemntSubsystem->unlockableAbilities[EntryName] = true;
			else if (PlayerAdvancemntSubsystem->metroidvaniaAbilities.Contains(EntryName))
				PlayerAdvancemntSubsystem->metroidvaniaAbilities[EntryName] = true;
		}
	}
}

bool UPlayerAdvancement::IsUnlock(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancement* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancement>())
		{
			if (PlayerAdvancemntSubsystem->scannableItems.Contains(EntryName))
				return PlayerAdvancemntSubsystem->scannableItems[EntryName];
			else if (PlayerAdvancemntSubsystem->collectableItems.Contains(EntryName))
				return PlayerAdvancemntSubsystem->collectableItems[EntryName];
			return false;
		}
	}
	return false;

}

bool UPlayerAdvancement::IsUnlockAbilities(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancement* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancement>())
		{
			if (PlayerAdvancemntSubsystem->unlockableAbilities.Contains(EntryName))
				return PlayerAdvancemntSubsystem->unlockableAbilities[EntryName];
			else if (PlayerAdvancemntSubsystem->metroidvaniaAbilities.Contains(EntryName))
				return PlayerAdvancemntSubsystem->metroidvaniaAbilities[EntryName];
			return false;
		}
	}
	return false;

}

void UPlayerAdvancement::UnlockItem(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancement* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancement>())
		{
			if (PlayerAdvancemntSubsystem->scannableItems.Contains(EntryName))
				PlayerAdvancemntSubsystem->scannableItems[EntryName] = true;
			else if (PlayerAdvancemntSubsystem->collectableItems.Contains(EntryName))
				PlayerAdvancemntSubsystem->collectableItems[EntryName] = true;
		}
	}
}

bool UPlayerAdvancement::GetScannableItemStatus(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancement* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancement>())
		{
			if (PlayerAdvancemntSubsystem->scannableItems.Contains(EntryName))
				return PlayerAdvancemntSubsystem->scannableItems[EntryName];
			return false;
		}
	}
	return false;
}

bool UPlayerAdvancement::GetUnlockableAbilities(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancement* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancement>())
		{
			if (PlayerAdvancemntSubsystem->unlockableAbilities.Contains(EntryName))
				return PlayerAdvancemntSubsystem->unlockableAbilities[EntryName];
			return false;
		}
	}
	return false;

}

bool UPlayerAdvancement::GetMetroidvaniaAbilities(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancement* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancement>())
		{
			if (PlayerAdvancemntSubsystem->metroidvaniaAbilities.Contains(EntryName))
				return PlayerAdvancemntSubsystem->metroidvaniaAbilities[EntryName];
			return false;
		}
	}
	return false;

}

bool UPlayerAdvancement::GetCollectableItems(FString EntryName)
{
	if (GEngine)
	{
		if (UPlayerAdvancement* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancement>())
		{
			if (PlayerAdvancemntSubsystem->collectableItems.Contains(EntryName))
				return PlayerAdvancemntSubsystem->collectableItems[EntryName];
			return false;
		}
	}
	return false;

}


void UPlayerAdvancement::SetScannableItemStatus(FString EntryName, bool isScanned)
{
	if (GEngine)
	{
		if (UPlayerAdvancement* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancement>())
		{
			if (PlayerAdvancemntSubsystem->scannableItems.Contains(EntryName)) PlayerAdvancemntSubsystem->scannableItems[EntryName] = isScanned;
		}
	}
}

void UPlayerAdvancement::SetUnlockableAbilities(FString EntryName, bool isUnlocked)
{
	if (GEngine)
	{
		if (UPlayerAdvancement* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancement>())
		{
			if (PlayerAdvancemntSubsystem->unlockableAbilities.Contains(EntryName)) PlayerAdvancemntSubsystem->unlockableAbilities[EntryName] = isUnlocked;
		}
	}
}
void UPlayerAdvancement::SetMetroidvaniaAbilities(FString EntryName, bool isUnlocked)
{
	if (GEngine)
	{
		if (UPlayerAdvancement* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancement>())
		{
			if (PlayerAdvancemntSubsystem->metroidvaniaAbilities.Contains(EntryName)) PlayerAdvancemntSubsystem->metroidvaniaAbilities[EntryName] = isUnlocked;
		}
	}
}
void UPlayerAdvancement::SetCollectableItems(FString EntryName, bool isCollected)
{
	if (GEngine)
	{
		if (UPlayerAdvancement* PlayerAdvancemntSubsystem = GEngine->GetEngineSubsystem<UPlayerAdvancement>())
		{
			if (PlayerAdvancemntSubsystem->collectableItems.Contains(EntryName)) PlayerAdvancemntSubsystem->collectableItems[EntryName] = isCollected;
		}
	}
}
