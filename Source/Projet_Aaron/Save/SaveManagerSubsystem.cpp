// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "AaronSaveGame.h"


//Constants to avoid mistyping the Index SlotName or UserIndex
static const FString	IndexSlotName	= "__SaveManagerIndex";
static const int32		IndexUserIndex	= 0;


static FString toOptionString(TMap<FString, FString>& Options)
{
	FString String;
	bool first = true;
	for (auto& Entry : Options)
	{
		//Separator logic (skip the first occurence then prefix with '?')
		if (first)
			first = false;
		else
			String.AppendChar('?');

		//Option logic
		String += FString::Printf(TEXT("%s=%s"), *Entry.Key, *Entry.Value);
	}
	return String;
}

bool operator==(const FSaveSlot& Lhs, const FSaveSlot& Rhs)
{
	return	Lhs.UserIndex == Rhs.UserIndex
		&&	Lhs.SlotName == Rhs.SlotName;
}

uint32 GetTypeHash(const FSaveSlot& SaveSlot)
{
	return GetTypeHash(SaveSlot.SlotName) ^ GetTypeHash(SaveSlot.UserIndex);
}

FSaveSlot::FSaveSlot()
	:	SlotName(),
		UserIndex(0)
{
}

USaveManagerIndex* USaveManagerSubsystem::GetIndex()
{
	//Index not Loaded or GarbageCollected
	if (!Index || !Index->IsValidLowLevel())
	{
		//Load from disk
		Index = Cast<USaveManagerIndex>(UGameplayStatics::LoadGameFromSlot(IndexSlotName, IndexUserIndex));

		if (!Index)
		{
			//Create Index (and persist to Disk)
			Index = Cast<USaveManagerIndex>(UGameplayStatics::CreateSaveGameObject(USaveManagerIndex::StaticClass()));
			UGameplayStatics::SaveGameToSlot(Index, IndexSlotName, IndexUserIndex);
		}
	}
	return Index;
}

void USaveManagerSubsystem::SaveIndex()
{
	if (Index)
	{
		UGameplayStatics::SaveGameToSlot(Index, IndexSlotName, IndexUserIndex);
	}
}

void USaveManagerSubsystem::GetSaveSlotList(TArray<FSaveSlot>& List)
{
	GetIndex()->Saves.GetKeys(List);
}

bool USaveManagerSubsystem::FindSaveInfo(const FSaveSlot& SaveSlot, FSaveInfo& SaveInfo)
{
	if (FSaveInfo* Value = GetIndex()->Saves.Find(SaveSlot))
	{
		SaveInfo = *Value;
		return true;
	}
	return false;
}

USaveGame* USaveManagerSubsystem::FindSaveGame(const FSaveSlot& SaveSlot)
{
	//Security check against unreferenced Slots
	if (GetIndex()->Saves.Find(SaveSlot))
	{
		return UGameplayStatics::LoadGameFromSlot(SaveSlot.SlotName, SaveSlot.UserIndex);
	}
	
	return nullptr;
}

void USaveManagerSubsystem::SaveGame(const FSaveSlot& SaveSlot, const FSaveInfo& SaveInfo, USaveGame* SaveGame)
{
	if (UGameplayStatics::SaveGameToSlot(SaveGame, SaveSlot.SlotName, SaveSlot.UserIndex))
	{
		//New Save or Override Save, same operation.
		GetIndex()->Saves.Add(SaveSlot, SaveInfo);
		SaveIndex();
	}
}

void USaveManagerSubsystem::DeleteGame(const FSaveSlot& SaveSlot)
{
	if (GetIndex()->Saves.Remove(SaveSlot))
	{
		UGameplayStatics::DeleteGameInSlot(SaveSlot.SlotName, SaveSlot.UserIndex);
		SaveIndex();
	}
}

void USaveManagerSubsystem::LoadGame(UObject* WorldContextObject, const FSaveSlot& SaveSlot, bool ForceOpenLevel)
{
	FSaveInfo SaveInfo;
	if (FindSaveInfo(SaveSlot, SaveInfo))
	{	
		const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(WorldContextObject);
		//Check if a level switch is required.
		if (ForceOpenLevel || CurrentLevelName != SaveInfo.LevelName)
		{
			const FName LevelFName(*SaveInfo.LevelName);

			TMap<FString, FString> Options;
			Options.Add("SlotName", SaveSlot.SlotName);
			Options.Add("UserIndex", FString::FromInt(SaveSlot.UserIndex));
			//MAYDO : Additional informations to forward ?

			// IMPORTANT : OpenLevel will wipe the current World in a somewhat async way.
			UGameplayStatics::OpenLevel(WorldContextObject, LevelFName, true, toOptionString(Options));
		}
		else
		{
			//Actual save loading
			UAaronSaveGame::LoadAaronSaveGame(WorldContextObject, SaveSlot.SlotName, SaveSlot.UserIndex);
		}
	}
}