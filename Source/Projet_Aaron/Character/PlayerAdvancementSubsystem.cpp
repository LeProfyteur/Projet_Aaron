// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAdvancementSubsystem.h"



void UPlayerAdvancementSubsystem::ClearPlayerAdvancement()
{
	Objectives.Empty();
	Scans.Empty();
	Collectibles.Empty();
	LogEntries.Empty();
}

void UPlayerAdvancementSubsystem::UpdateObjective(FName ObjectiveID, bool Status)
{
	Objectives.Add(ObjectiveID, Status);
}

void UPlayerAdvancementSubsystem::UpdateScan(FName ScanID, bool Status)
{
	Scans.Add(ScanID, Status);
}

void UPlayerAdvancementSubsystem::UpdateCollectible(FName CollectibleID, bool Status)
{
	Collectibles.Add(CollectibleID, Status);
}

void UPlayerAdvancementSubsystem::UpdateLogEntry(FName EntryID, bool Status)
{
	LogEntries.Add(EntryID, Status);
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
