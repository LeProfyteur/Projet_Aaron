// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerAdvancementSubsystem.generated.h"


UCLASS()
class PROJET_AARON_API UPlayerAdvancementSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void ClearPlayerAdvancement();

	UFUNCTION(BlueprintCallable)
		void SaveData();
	UFUNCTION(BlueprintCallable)
		void LoadData();
	
	UFUNCTION(BlueprintCallable)
		void UpdateSpawnPoint(FName NewLevelName, FName NewSpawnPointName);
	UFUNCTION(BlueprintCallable)
		void RegisterSpawnPoint(APlayerStart* SpawnPoint);
	UFUNCTION(BlueprintCallable)
		void UnregisterSpawnPoint(APlayerStart* SpawnPoint);
	UFUNCTION(BlueprintCallable)
		APlayerStart* GetSpawnPoint();

	UFUNCTION(BlueprintCallable)
        void UpdateObjective(FName ObjectiveID, bool Status);
    UFUNCTION(BlueprintCallable)
        void UpdateScan(FName ScanID, bool Status);
    UFUNCTION(BlueprintCallable)
        void UpdateSkill(FName SkillID, bool Status);
	UFUNCTION(BlueprintCallable)
		void UpdateCollectible(FName CollectibleID, bool Status);
	UFUNCTION(BlueprintCallable)
		void UpdateLogEntry(FName EntryID, bool Status);

	UFUNCTION(BlueprintCallable)
		bool GetObjectiveStatus(FName ObjectiveID) const;
    UFUNCTION(BlueprintCallable)
        bool GetScanStatus(FName ScanID) const;
    UFUNCTION(BlueprintCallable)
        bool GetSkillStatus(FName SkillID) const;
	UFUNCTION(BlueprintCallable)
		bool GetCollectibleStatus(FName CollectibleID) const;
	UFUNCTION(BlueprintCallable)
		bool GetLogEntryStatus(FName LogEntryID) const;

	UFUNCTION(BlueprintCallable)
		FName GetLevelName();
	UFUNCTION(BlueprintCallable)
		FName GetSpawnPointName();

protected:
	UPROPERTY(BlueprintReadOnly)
		TMap<FName, bool> Objectives;
	UPROPERTY(BlueprintReadOnly)
		TMap<FName, bool> Scans;
	UPROPERTY(BlueprintReadOnly)
		TMap<FName, bool> Skills;
	UPROPERTY(BlueprintReadOnly)
		TMap<FName, bool> Collectibles;
	UPROPERTY(BlueprintReadOnly)
		TMap<FName, bool> LogEntries;

	UPROPERTY(BlueprintReadOnly)
		FName LevelName = NAME_None;
	UPROPERTY(BlueprintReadOnly)
		FName SpawnPointName = NAME_None;

	UPROPERTY(Transient, BlueprintReadOnly)
		TArray<APlayerStart*> SpawnPoints;
};