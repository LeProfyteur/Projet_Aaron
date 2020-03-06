// Fill out your copyright notice in the Description page of Project Settings.

#include "AaronSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Misc/Paths.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Engine/World.h"

UAaronSaveGame::UAaronSaveGame()
{
}

void UAaronSaveGame::Save(AActor* Actor)
{
	if (!Actor) return;

	//Emplace a new Actor in the save
	int32 Index = Actors.Emplace();
	FActorRecord& Record = Actors[Index];

	//Configure the Record data
	Record.Class = Actor->GetClass();
	Record.Name = Actor->GetFName();
	Record.Transform = Actor->GetTransform();
	Serialize(Actor, Record.ActorData);
}

void UAaronSaveGame::PreLoad(UObject* WorldContextObject, FActorRecord& Record)
{
	if (!WorldContextObject || !WorldContextObject->GetWorld())
	{
		UE_LOG(LogLevel, Error, TEXT("Require valid a WorldContext to Preload Actors"));
		return;
	}

	if (!Record.Class)
	{
		UE_LOG(LogLevel, Error, TEXT("Failed to load Record because Class is not present"))	;
		return;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Name = Record.Name;

	UE_LOG(LogLevel, Display, TEXT("Spawning %s %s"), *Record.Class->GetName(), *Record.Name.ToString());
	AActor* Actor = WorldContextObject->GetWorld()->SpawnActor<AActor>(Record.Class.Get(), Record.Transform, SpawnParameters);

	if (!Actor)
	{
		UE_LOG(LogLevel, Error, TEXT("Failed to Spawn %s %s"), *Record.Class->GetName(), *Record.Name.ToString());
		return;
	}

	//Scale seems not affected by the Transform specification
	Actor->SetActorScale3D(Record.Transform.GetScale3D());
}

void UAaronSaveGame::PostLoad(AActor* Actor, FActorRecord& Record)
{
	if (!Actor) return;
	Deserialize(Actor, Record.ActorData);
}

void UAaronSaveGame::Serialize(UObject* Object, UPARAM(ref) TArray<uint8>& Buffer)
{
	if (Object)
	{
		FMemoryWriter MemoryWriter = FMemoryWriter(Buffer, true);
		FObjectAndNameAsStringProxyArchive Archive = FObjectAndNameAsStringProxyArchive(MemoryWriter, true);
		Archive.ArIsSaveGame = true;
		Archive.ArNoDelta = true;

		Object->Serialize(Archive);
	}
}

void UAaronSaveGame::Deserialize(UObject* Object, UPARAM(ref) TArray<uint8>& Buffer)
{
	if (Object)
	{
		UE_LOG(LogLevel, Warning, TEXT("Deserializing %s"), *Object->GetName());
		FMemoryReader MemoryReader(Buffer, true);
		FObjectAndNameAsStringProxyArchive Archive = FObjectAndNameAsStringProxyArchive(MemoryReader, true);
		Archive.ArIsSaveGame = true;
		Archive.ArNoDelta = true;

		Object->Serialize(Archive);
	}
}

void UAaronSaveGame::SaveAaronSaveGame(UObject* WorldContextObject, const FString& SlotName, int32 UserIndex)
{
	if (UAaronSaveGame* SaveGame = Cast<UAaronSaveGame>(UGameplayStatics::CreateSaveGameObject(UAaronSaveGame::StaticClass())))
	{
		//Save Level context
		SaveGame->LevelName = UGameplayStatics::GetCurrentLevelName(WorldContextObject);

		TArray<AActor*> PersistentActors;
		UGameplayStatics::GetAllActorsWithTag(WorldContextObject, "AaronPersistent", PersistentActors);
		for (auto Actor : PersistentActors)
		{
			SaveGame->Save(Actor);
		}

		//Persist SaveGame
		UGameplayStatics::SaveGameToSlot(SaveGame, SlotName, UserIndex);
	}
}

void UAaronSaveGame::LoadAaronSaveGame(UObject* WorldContextObject, const FString& SlotName, int32 UserIndex)
{
	if (UAaronSaveGame* SaveGame = Cast<UAaronSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex)))
	{	
		//Instantiate all Actors in the World (without applying their presets)
		for (FActorRecord& Record : SaveGame->Actors)
		{
			SaveGame->PreLoad(WorldContextObject, Record);
		}
		
		//Configure all instantiated Actors deserializing their respective Records
		for (FActorRecord& Record : SaveGame->Actors)
		{		
//			AActor* Actor = SaveGame->ActorSerializationContext.FindRef(Record.UniqueID);
//			SaveGame->PostLoad(Actor, Record);
		}
		
		UE_LOG(LogLevel, Warning, TEXT("Loaded SaveGame %s with %d Actors"), *SlotName, SaveGame->Actors.Num());
	}
}