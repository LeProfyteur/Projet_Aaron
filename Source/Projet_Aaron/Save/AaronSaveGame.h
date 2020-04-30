// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/SaveGame.h"
#include "GameFramework/Actor.h"

#include "AaronSaveGame.generated.h"

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
		FString LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
		FDateTime Date;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
		FTimespan PlayTime;


	FORCEINLINE FArchive& Serialize(FArchive& Ar)
	{
		Ar << LevelName;
		Ar << Date;
		Ar << PlayTime;
		return Ar;
	}
};

/**
 * DialogSubsystemRecord is the persistent version of the Dialog subsystem.
 * Broken ATM.
 */
USTRUCT(BlueprintType)
struct FDialogSubsystemRecord
{
	GENERATED_BODY()
public:
	
	UPROPERTY(SaveGame)
		TMap<FString, int32> Metrics;

	UPROPERTY(SaveGame)
		TMap<FString, bool> Knowledge;

	UPROPERTY(SaveGame)
		TMap<FString, bool> Dialog;

	FORCEINLINE FArchive& Serialize(FArchive& Ar)
	{
		Ar << Metrics;
		Ar << Knowledge;
		Ar << Dialog;
		return Ar;
	}
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
	
	/**
	 * Name of the level to open
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ProjetAaron")
		FString LevelName;

	/**
	 * Configuration of the Subsystems
	 */
	UPROPERTY(VisibleAnywhere, Category = "ProjetAaron")
		FDialogSubsystemRecord DialogSubsystemRecord;

	/**
	 * Array of all the persisted Actors (without hierarchy)
	 */
	UPROPERTY(VisibleAnywhere, Category = "ProjetAaron")
		TArray<FActorRecord> Actors;

	/**
	 * Array of all the persisted ActorComponents (without hierarchy)
	 */
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

	void SaveActor(AActor* Actor);
	void LoadActor(UWorld* World, UPARAM(ref) FActorRecord& ActorRecord);

	void SaveComponent(UActorComponent* Component);
	void LoadComponent(UWorld* World, AActor* Actor, UPARAM(ref) FComponentRecord& ComponentRecord);
	
	//--------------------------------------------------------------------------//
	// Static Utility Functions
	//--------------------------------------------------------------------------//
	
	static void Serialize(UObject* Object, UPARAM(ref) TArray<uint8>& Buffer);
	
	static void Deserialize(UObject* Object, UPARAM(ref) TArray<uint8>& Buffer);
};