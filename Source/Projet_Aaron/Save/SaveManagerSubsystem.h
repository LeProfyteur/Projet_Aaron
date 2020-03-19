// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "GameFramework/SaveGame.h"
#include "SaveManagerSubsystem.generated.h"

/**
 * SaveSlot represents an UE4 SaveGame slot.
 * This is essentially a Key pairing SlotName and UserIndex
 */
USTRUCT(BlueprintType)
struct FSaveSlot
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
		FString SlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
		int32 UserIndex;

	FSaveSlot();
};
bool operator==(const FSaveSlot& Lhs, const FSaveSlot& Rhs);
uint32 GetTypeHash(const FSaveSlot& SaveSlot);


/**
 * SaveInfo represents the details of the header of a SaveGame.
 * It has a few fields that are managed by the index.
 */
USTRUCT(BlueprintType)
struct FSaveInfo
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
		FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
		FString LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
		FDateTime Date;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
		FTimespan PlayTime;
};

/**
 * This file represents the list of all FSaveSlot entries managed by that Index.
 * The SaveManagerIndex class is used internal by the SaveManager to store/fetch the list of saves.
 */
UCLASS()
class USaveManagerIndex : public USaveGame
{
	GENERATED_BODY()
public:
	
	UPROPERTY(SaveGame)
		TMap<FSaveSlot, FSaveInfo> Saves;
};

/**
 * Subsystem that manages SaveGames using an Index
 */
UCLASS()
class PROJET_AARON_API USaveManagerSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()


private:
	USaveManagerIndex* Index;
	
public:
	USaveManagerIndex* GetIndex();
	void SaveIndex();

	UFUNCTION(BlueprintCallable)
		void GetSaveSlotList(TArray<FSaveSlot>& List);

	UFUNCTION(BlueprintCallable)
		bool FindSaveInfo(const FSaveSlot& SaveSlot, FSaveInfo& SaveInfo);

	UFUNCTION(BlueprintCallable)
		USaveGame* FindSaveGame(const FSaveSlot& SaveSlot);

	UFUNCTION(BlueprintCallable)
		void SaveGame(const FSaveSlot& SaveSlot, const FSaveInfo& SaveInfo, USaveGame* SaveGame);

	UFUNCTION(BlueprintCallable)
		void DeleteGame(const FSaveSlot& SaveSlot);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
		void LoadGame(UObject* WorldContextObject, const FSaveSlot& SaveSlot, bool ForceOpenLevel);
};