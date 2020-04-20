// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/SaveGame.h"
#include "GameFramework/Actor.h"

#include "AaronSaveGame.generated.h"

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

private:
	//--------------------------------------------------------------------------//
	// AaronSaveGame Functions
	//--------------------------------------------------------------------------//
	void SaveActor(AActor* Actor);
	void LoadActor(UObject* WorldContextObject, UPARAM(ref) FActorRecord& ActorRecord);

	void SaveComponent(UActorComponent* Component);
	void LoadComponent(UObject* WorldContextObject, AActor* Actor, UPARAM(ref) FComponentRecord& ComponentRecord);
	
	void Save(UObject* WorldContextObject);
	void Load(UObject* WorldContextObject);
	
	void FindComponentsForActor(uint32 ActorUniqueID, TArray<FComponentRecord*>& Records); // MAYDO : optimize that to avoid copying data around
public:
	//--------------------------------------------------------------------------//
	// Static Utility Functions
	//--------------------------------------------------------------------------//
	
	static void Serialize(UObject* Object, UPARAM(ref) TArray<uint8>& Buffer);
	
	static void Deserialize(UObject* Object, UPARAM(ref) TArray<uint8>& Buffer);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static UAaronSaveGame* CreateAaronSaveGame(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void LoadAaronSaveGame(UObject* WorldContextObject, const FString& SlotName, int32 UserIndex);
};