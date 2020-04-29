// Fill out your copyright notice in the Description page of Project Settings.

#include "AaronSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Misc/Paths.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Engine/World.h"
#include "UObject/UObjectIterator.h"
#include "AaronPersistentComponent.h"
#include "Projet_Aaron/Dialog/DialogSubsystem.h"

static inline UActorComponent* GetComponentByFName(AActor* Owner, const FName& Name)
{
	for (UActorComponent* Component : Owner->GetComponents())
	{
		if (Component && Component->GetFName() == Name)
			return Component;
	}
	return nullptr;
}

UAaronSaveGame::UAaronSaveGame()
{
}

void UAaronSaveGame::Save(UObject* WorldContextObject)
{
	//TODO : manually save each subsystem

	SaveInfo.LevelName = WorldContextObject->GetWorld()->GetName();
	SaveInfo.Date = FDateTime::Now();
}

void UAaronSaveGame::Load(UObject* WorldContextObject)
{
	//TODO : manually load each subsystem
	
	for (auto& Record : Actors)
	{
		LoadActor(WorldContextObject->GetWorld(), Record);
	}
}

void UAaronSaveGame::SaveActor(AActor* Actor)
{
	//Reject invalid call
	if (!Actor) return;

	//Reject if Not Persistent or marked as Transient
	UAaronPersistentComponent* Persistence = Actor->FindComponentByClass<UAaronPersistentComponent>();
	if (!Persistence) return;
	if (Persistence->Transient) return;

	//Pre-Save Persistence event Broadcast
	Persistence->OnSave.Broadcast();

	//Reject If Already Saved
	for (const FActorRecord& Record : Actors)
	{
		if (Record.Reference == Actor)
			return;
	}
	
	//UE_LOG(LogSerialization, Display, TEXT("Saving Actor %s %s"), *Actor->GetClass()->GetName(), *Actor->GetName());

	//Serialize the Actor
	int32 Index = Actors.Emplace();
	FActorRecord& Record = Actors[Index];
	Record.Reference = Actor;
	Record.UniqueID = Actor->GetUniqueID();
	Record.ParentID = Actor->GetParentActor() ? Actor->GetParentActor()->GetUniqueID() : uint32(INDEX_NONE);
	Record.Class = Actor->GetClass();
	Record.Name = Actor->GetFName();
	Record.Transform = Actor->GetTransform();
	Serialize(Actor, Record.ActorData);

	//Serialize the Actor Components
	for (auto ActorComponent : Actor->GetComponents())
	{
		if (ActorComponent)
		{
			SaveComponent(ActorComponent);
		}
	}
}

void UAaronSaveGame::LoadActor(UWorld* World, UPARAM(ref) FActorRecord& ActorRecord)
{
	//Reject already Deserialized Record
	if (ActorRecord.Reference) return;
	
	//Instantiate Actor & load serialized data
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Name = ActorRecord.Name;
	UClass* ActorClass = ActorRecord.Class.Get();
	AActor* Actor = World->SpawnActorDeferred<AActor>(ActorClass, ActorRecord.Transform);
	Deserialize(Actor, ActorRecord.ActorData);
	UGameplayStatics::FinishSpawningActor(Actor, ActorRecord.Transform);

	//Instantiate Components
	TArray<FComponentRecord*> ActorComponents;
	FindComponentsForActor(ActorRecord.UniqueID, ActorComponents);
	for (auto ComponentRecord : ActorComponents)
	{
		LoadComponent(World, Actor, *ComponentRecord);
	}

	//Post-load Persistence Event Broadcast
	if (UAaronPersistentComponent* Persistence = Actor->FindComponentByClass<UAaronPersistentComponent>())
	{
		Persistence->OnLoad.Broadcast();
	}
}

void UAaronSaveGame::SaveComponent(UActorComponent* Component)
{
	//Reject invalid call
	if (!Component) return;
	if (!Component->GetOwner()) return;
	
	//UE_LOG(LogSerialization, Display, TEXT("Saving Component %s %s"), *Component->GetClass()->GetName(), *Component->GetName());

	const int32 Index = Components.Emplace();
	FComponentRecord& Record = Components[Index];
	Record.Reference = nullptr; // this property is used for loading only
	Record.Class = Component->GetClass();
	Record.OwnerID = Component->GetOwner()->GetUniqueID();
	Record.UniqueID = Component->GetUniqueID();
	Record.Name = Component->GetFName();
	Serialize(Component, Record.ComponentData);
}

void UAaronSaveGame::LoadComponent(UWorld* World, AActor* Actor, UPARAM(ref)FComponentRecord& ComponentRecord)
{
	//Reject already deserialized Records
	if (ComponentRecord.Reference) return;

	//UE_LOG(LogSerialization, Display, TEXT("Loading Component %s %s"), *ComponentRecord.Class->GetName(), *ComponentRecord.Name.ToString());
}

void UAaronSaveGame::FindComponentsForActor(uint32 ActorUniqueID, TArray<FComponentRecord*>& Records)
{
	Records.Reset();
	for (auto& Record : Components)
	{
		if (Record.OwnerID == ActorUniqueID)
			Records.Add(&Record);
	}
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