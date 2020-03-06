// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"


//Constants to avoid mistyping the Index SlotName or UserIndex
static const FString	IndexSlotName	= "__SaveManagerIndex";
static const int32		IndexUserIndex	= 0;


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
		GetIndex()->Saves[SaveSlot] = SaveInfo;
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