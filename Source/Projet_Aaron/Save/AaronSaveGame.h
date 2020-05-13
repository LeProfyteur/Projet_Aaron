// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/SaveGame.h"
#include "GameFramework/Actor.h"

#include "AaronSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FSaveInfo
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
		FString LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
		FDateTime Date;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
		FTimespan PlayTime;
};

USTRUCT(BlueprintType)
struct FSubsystemData
{
	GENERATED_BODY()
public:

	/* Dialog Subsystem Data */
	UPROPERTY(SaveGame)
		TMap<FString, int32> Metrics;
	UPROPERTY(SaveGame)
		TMap<FString, bool> Knowledge;
	UPROPERTY(SaveGame)
		TMap<FString, bool> Dialog;

	/* Spawn Subsystem Data */
	UPROPERTY(SaveGame)
		FString RespawnLevelName;
	UPROPERTY(SaveGame)
		FString RespawnPlayerStartTag;
	UPROPERTY(SaveGame)
		FString PreferredPlayerStartTag;

	/* Player Advancement Data */
	UPROPERTY(SaveGame)
		TMap<FString, bool> ScannableItems;
	UPROPERTY(SaveGame)
		TMap<FString, bool> CollectableItems;
	UPROPERTY(SaveGame)
		TMap<FString, bool> UnlockableAbilities;
	UPROPERTY(SaveGame)
		TMap<FString, bool> MetroidvaniaAbilities;
	UPROPERTY(SaveGame)
		TMap<FString, bool> CollectableItemsCompleted;
};

USTRUCT(BlueprintType)
struct FComponentRecord
{
	GENERATED_BODY()
public:

	UPROPERTY(Transient)
		UActorComponent* Reference;

	UPROPERTY(SaveGame)
		TSubclassOf<UActorComponent> Class;

	UPROPERTY(SaveGame)
		uint32 OwnerID;

	UPROPERTY(SaveGame)
		uint32 UniqueID;

	UPROPERTY(SaveGame)
		FName Name;

	UPROPERTY(SaveGame)
		TArray<uint8> ComponentData;

	FORCEINLINE FArchive& Serialize(FArchive& Ar)
	{
		Ar << Class;
		Ar << OwnerID;
		Ar << UniqueID;
		Ar << Name;
		Ar << ComponentData;
		return Ar;
	}
};


USTRUCT(BlueprintType)
struct FActorRecord
{
	GENERATED_BODY()
public:

	UPROPERTY(Transient)
		AActor* Reference;
	
	UPROPERTY(SaveGame)
		TSubclassOf<AActor> Class;

	UPROPERTY(SaveGame)
		uint32 UniqueID;

	UPROPERTY(SaveGame)
		uint32 ParentID;
	
	UPROPERTY(SaveGame)
		FName Name;
	
	UPROPERTY(SaveGame)
		FTransform Transform;

	UPROPERTY(SaveGame)
		TArray<uint8> ActorData;

	FORCEINLINE FArchive& Serialize(FArchive& Ar)
	{
		Ar << Class;
		Ar << UniqueID;
		Ar << ParentID;
		Ar << Name;
		Ar << Transform;
		Ar << ActorData;
		return Ar;
	}
};

UCLASS(BlueprintType)
class PROJET_AARON_API UAaronSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	/**
	 * 
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ProjetAaron")
		FSaveInfo SaveInfo;

	UPROPERTY(VisibleAnywhere, Category = "ProjetAaron")
		FSubsystemData SubsystemData;

	UPROPERTY(VisibleAnywhere, Category = "ProjetAaron")
		TArray<FActorRecord> Actors;

	UPROPERTY(VisibleAnywhere, Category = "ProjetAaron")
		TArray<FComponentRecord> Components;
	
	/**
	 * Default constructor
	 */
	UAaronSaveGame();	

	//--------------------------------------------------------------------------//
	// AaronSaveGame Functions
	//--------------------------------------------------------------------------//
	void Save(UObject* WorldObjectContext);
	void Load(UObject* WorldObjectContext);

	void SaveSubsystemData(UObject* WorldObjectContext);
	void LoadSubsystemData(UObject* WorldObjectContext);

	void SaveActor(AActor* Actor);
	void LoadActor(UWorld* World, UPARAM(ref) FActorRecord& ActorRecord);

	void SaveComponent(UActorComponent* Component);
	void LoadComponent(UWorld* World, AActor* Actor, UPARAM(ref) FComponentRecord& ComponentRecord);
	
	//--------------------------------------------------------------------------//
	// Static Utility Functions
	//--------------------------------------------------------------------------//
	
	static void SerializeObject(UObject* Object, UPARAM(ref) TArray<uint8>& Buffer);
	
	static void DeserializeObject(UObject* Object, UPARAM(ref) TArray<uint8>& Buffer);
};