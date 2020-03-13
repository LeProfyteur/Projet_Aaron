// Fill out your copyright notice in the Description page of Project Settings.

#include "AaronSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Misc/Paths.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Engine/World.h"
#include "UObject/UObjectIterator.h"
#include "AaronPersistentComponent.h"

UAaronSaveGame::UAaronSaveGame()
{
}

void UAaronSaveGame::SaveActor(AActor* Actor)
{
	//Reject invalid call
	if (!Actor) return;

	//Detect Transient Actors
	UAaronPersistentComponent* Persistence = Actor->FindComponentByClass<UAaronPersistentComponent>();
	if (!Persistence) return;
	if (Persistence->Transient) return;
		
	//Serialize Actor
	int32 Index = Actors.Emplace();
	FActorRecord& Record = Actors[Index];
	Record.UniqueID = Actor->GetUniqueID();
	Record.ParentID = Actor->GetParentActor() ? Actor->GetParentActor()->GetUniqueID() : uint32(INDEX_NONE);
	Record.Class = Actor->GetClass();
	Record.Name = Actor->GetFName();
	Record.Transform = Actor->GetTransform();
	Serialize(Actor, Record.ActorData);

	//Serialize Actor's Components
	for (auto ActorComponent : Actor->GetComponents())
	{
		if (ActorComponent)
		{
			SaveComponent(ActorComponent);
		}
	}

	//Serialize Actor's Children (direct children only)
	TArray<AActor*> ChildActors;
	Actor->GetAllChildActors(ChildActors, false);
	for (auto ChildActor : ChildActors)
	{
		SaveActor(ChildActor);
	}
}

void UAaronSaveGame::SaveComponent(UActorComponent* Component)
{
	//Reject invalid call
	if (!Component) return;
	if (!Component->GetOwner()) return;

	int32 Index = Components.Emplace();
	FComponentRecord& Record = Components[Index];
	Record.Class = Component->GetClass();
	Record.OwnerID = Component->GetOwner()->GetUniqueID();
	Record.UniqueID = Component->GetUniqueID();
	Record.Name = Component->GetFName();
	Serialize(Component, Record.ComponentData);
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
		FMemoryReader MemoryReader(Buffer, true);
		FObjectAndNameAsStringProxyArchive Archive = FObjectAndNameAsStringProxyArchive(MemoryReader, true);
		Archive.ArIsSaveGame = true;
		Archive.ArNoDelta = true;

		Object->Serialize(Archive);
	}
}

UAaronSaveGame* UAaronSaveGame::CreateAaronSaveGame(UObject* WorldContextObject)
{
	if (UAaronSaveGame* SaveGame = Cast<UAaronSaveGame>(UGameplayStatics::CreateSaveGameObject(UAaronSaveGame::StaticClass())))
	{
		//Persist all Actors
		for (TObjectIterator<AActor> Itr; Itr; ++Itr)
		{
			SaveGame->SaveActor(*Itr);
		}
		
		return SaveGame;
	}
	return nullptr;
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