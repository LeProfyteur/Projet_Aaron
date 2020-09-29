// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerAdvancementSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UPlayerAdvancementSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(SaveGame)
		TMap<FName, bool> Objectives;
	UPROPERTY(SaveGame)
		TMap<FName, bool> Scans;
	UPROPERTY(SaveGame)
		TMap<FName, bool> Skills;
	UPROPERTY(SaveGame)
		TMap<FName, bool> Collectibles;
	UPROPERTY(SaveGame)
		TMap<FName, bool> LogEntries;

	UPROPERTY(SaveGame)
		FName LevelName;
	UPROPERTY(SaveGame)
		FName SpawnPointName;
};
