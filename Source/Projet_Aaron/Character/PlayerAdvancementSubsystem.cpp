// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAdvancementSubsystem.h"
#include "Projet_Aaron/GameplayEvents/GameplayEventsSubsystem.h"
#include "Engine/GameInstance.h"


void UPlayerAdvancementSubsystem::ClearPlayerAdvancement()
{
	Objectives.Empty();
	Scans.Empty();
	Collectibles.Empty();
	LogEntries.Empty();
}

void UPlayerAdvancementSubsystem::UpdateObjective(FName ObjectiveID, bool Status)
{
	bool* Previous = Objectives.Find(ObjectiveID);
	if (Previous == nullptr || *Previous != Status)
	{
		Objectives.Add(ObjectiveID, Status);
		if (UGameplayEventsSubsystem* GameplayEvents = GetGameInstance()->GetSubsystem<UGameplayEventsSubsystem>())
		{
			GameplayEvents->SignalPlayerObjectiveUpdate(ObjectiveID);
		}
	}
}

void UPlayerAdvancementSubsystem::UpdateScan(FName ScanID, bool Status)
{
	bool* Previous = Scans.Find(ScanID);
	if (Previous == nullptr || *Previous != Status)
	{
		Scans.Add(ScanID, Status);
		if (UGameplayEventsSubsystem* GameplayEvents = GetGameInstance()->GetSubsystem<UGameplayEventsSubsystem>())
		{
			GameplayEvents->SignalPlayerScanUpdate(ScanID);
		}
	}
}

void UPlayerAdvancementSubsystem::UpdateSkill(FName SkillID, bool Status)
{
	bool* Previous = Skills.Find(SkillID);
	if (Previous == nullptr || *Previous != Status)
	{
		Skills.Add(SkillID, Status);
		if (UGameplayEventsSubsystem* GameplayEvents = GetGameInstance()->GetSubsystem<UGameplayEventsSubsystem>())
		{
			GameplayEvents->SignalPlayerSkillUpdate(SkillID);
		}
	}
}

void UPlayerAdvancementSubsystem::UpdateCollectible(FName CollectibleID, bool Status)
{
	bool* Previous = Collectibles.Find(CollectibleID);
	if (Previous == nullptr || *Previous != Status)
	{
		Collectibles.Add(CollectibleID, Status);
		if (UGameplayEventsSubsystem* GameplayEvents = GetGameInstance()->GetSubsystem<UGameplayEventsSubsystem>())
		{
			GameplayEvents->SignalPlayerCollectibleUpdate(CollectibleID);
		}
	}
}

void UPlayerAdvancementSubsystem::UpdateLogEntry(FName EntryID, bool Status)
{
	bool* Previous = LogEntries.Find(EntryID);
	if (Previous == nullptr || *Previous != Status)
	{
		LogEntries.Add(EntryID, Status);
		if (UGameplayEventsSubsystem* GameplayEvents = GetGameInstance()->GetSubsystem<UGameplayEventsSubsystem>())
		{
			GameplayEvents->SignalPlayerLogEntryUpdate(EntryID);
		}
	}
}

bool UPlayerAdvancementSubsystem::GetObjectiveStatus(FName ObjectiveID) const
{
	const bool* Result = Objectives.Find(ObjectiveID);
	return Result != nullptr && *Result;
}

bool UPlayerAdvancementSubsystem::GetScanStatus(FName ScanID) const
{
    const bool* Result = Scans.Find(ScanID);
    return Result != nullptr && *Result;
}

bool UPlayerAdvancementSubsystem::GetSkillStatus(FName ScanID) const
{
    const bool* Result = Skills.Find(ScanID);
    return Result != nullptr && *Result;
}

bool UPlayerAdvancementSubsystem::GetCollectibleStatus(FName CollectibleID) const
{
	const bool* Result = Collectibles.Find(CollectibleID);
	return Result != nullptr && *Result;
}

bool UPlayerAdvancementSubsystem::GetLogEntryStatus(FName LogEntryID) const
{
	const bool* Result = LogEntries.Find(LogEntryID);
	return Result != nullptr && *Result;
}
