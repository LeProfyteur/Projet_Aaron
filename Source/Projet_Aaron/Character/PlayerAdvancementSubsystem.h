// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerAdvancementSubsystem.generated.h"


UCLASS()
class PROJET_AARON_API UPlayerAdvancementSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	TMap<FName, bool> Objectives;
	TMap<FName, bool> Scans;
	TMap<FName, bool> Collectibles;
	TMap<FName, bool> LogEntries;

public:
	UFUNCTION(BlueprintCallable)
		void ClearPlayerAdvancement();
	
	UFUNCTION(BlueprintCallable)
		void UpdateObjective(FName ObjectiveID, bool Status);
	UFUNCTION(BlueprintCallable)
		void UpdateScan(FName ScanID, bool Status);
	UFUNCTION(BlueprintCallable)
		void UpdateCollectible(FName CollectibleID, bool Status);
	UFUNCTION(BlueprintCallable)
		void UpdateLogEntry(FName EntryID, bool Status);

	UFUNCTION(BlueprintCallable)
		bool GetObjectiveStatus(FName ObjectiveID) const;
	UFUNCTION(BlueprintCallable)
		bool GetScanStatus(FName ScanID) const;
	UFUNCTION(BlueprintCallable)
		bool GetCollectibleStatus(FName CollectibleID) const;
	UFUNCTION(BlueprintCallable)
		bool GetLogEntryStatus(FName LogEntryID) const;
};
