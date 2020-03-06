// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/SaveGame.h"
#include "GameFramework/Actor.h"

#include "AaronSaveGame.generated.h"


//WIP : This Structure will represent a serialized Component. NOT USEABLE YET
USTRUCT(BlueprintType)
struct FComponentRecord
{
	GENERATED_BODY()
public:

	UPROPERTY(SaveGame)
		TSubclassOf<UActorComponent> Class;

	UPROPERTY(SaveGame)
		TArray<uint8> ComponentData;

	FORCEINLINE FArchive& Serialize(FArchive& Ar)
	{
		Ar << Class;
		Ar << ComponentData;
		return Ar;
	}
};


USTRUCT(BlueprintType)
struct FActorRecord
{
	GENERATED_BODY()
public:
	
	UPROPERTY(SaveGame)
		TSubclassOf<AActor> Class;
	
	UPROPERTY(SaveGame)
		FName Name;
	
	UPROPERTY(SaveGame)
		FTransform Transform;

	UPROPERTY(SaveGame)
		TArray<uint8> ActorData;

	UPROPERTY(SaveGame)
		TArray<FComponentRecord> ComponentRecords;

	FORCEINLINE FArchive& Serialize(FArchive& Ar)
	{
		Ar << Class;
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
	 * Array of all the persisted Actors
	 */
	UPROPERTY(VisibleAnywhere, Category = "ProjetAaron")
	TArray<FActorRecord> Actors;

	/**
	 * Default constructor
	 */
	UAaronSaveGame();	

private:
	//--------------------------------------------------------------------------//
	// AaronSaveGame Functions
	//--------------------------------------------------------------------------//
	void Save(AActor* Actor);
	void PreLoad(UObject* WorldContextObject, FActorRecord& Record);
	void PostLoad(AActor* Actor, FActorRecord& Record);

public:
	//--------------------------------------------------------------------------//
	// Static Utility Functions
	//--------------------------------------------------------------------------//

	//TODO : list save games ?
	
	static void Serialize(UObject* Object, UPARAM(ref) TArray<uint8>& Buffer);
	
	static void Deserialize(UObject* Object, UPARAM(ref) TArray<uint8>& Buffer);
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void SaveAaronSaveGame(UObject* WorldContextObject, const FString& SlotName, int32 UserIndex);
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void LoadAaronSaveGame(UObject* WorldContextObject, const FString& SlotName, int32 UserIndex);
};