// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "AaronSaveManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "AaronSaveGame.h"
#include "EngineUtils.h"

const int32 UAaronSaveManagerSubsystem::MaxSaveSlots = 50;


UAaronSaveManagerSubsystem::UAaronSaveManagerSubsystem()
{
	CurrentSaveSlot = -1;
	LoadingSaveGame = nullptr;
	DateBeginPlay = FDateTime::Now();
}

FString UAaronSaveManagerSubsystem::GetSaveSlotName(int32 SaveSlot)
{
	return FString::Printf(TEXT("Save_%2d"), SaveSlot);
}

void UAaronSaveManagerSubsystem::RefreshDateBeginPlay()
{
	DateBeginPlay = FDateTime::Now();
}

FTimespan UAaronSaveManagerSubsystem::GetElapsedPlayTime()
{
	return FDateTime::Now() - DateBeginPlay;
}

void UAaronSaveManagerSubsystem::GetSaveList(TArray<int32>& List)
{
	List.Reset();
	for (int32 Index = 0; Index < MaxSaveSlots; Index++)
	{
		FString SaveSlotName = GetSaveSlotName(Index);
		if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
		{
			List.Add(Index);
		}
	}
}

int32 UAaronSaveManagerSubsystem::GetEmptySaveSlotIndex()
{
	for (int32 Index = 0; Index < MaxSaveSlots; Index++)
	{
		FString SaveSlotName = GetSaveSlotName(Index);
		if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
		{
			continue;
		}
		return Index;
	}
	return -1;
}

void UAaronSaveManagerSubsystem::DeleteGame(int32 SaveSlot)
{
	UGameplayStatics::DeleteGameInSlot(GetSaveSlotName(SaveSlot), 0);
}

void UAaronSaveManagerSubsystem::Save()
{
	ensureMsgf(CurrentSaveSlot >= 0 && CurrentSaveSlot < MaxSaveSlots, TEXT("CurrentSaveSlot is not set."));
	UAaronSaveGame* SaveGame = Cast<UAaronSaveGame>(UGameplayStatics::CreateSaveGameObject(UAaronSaveGame::StaticClass()));

	SaveGame->Save(this);

	UGameplayStatics::SaveGameToSlot(SaveGame, GetSaveSlotName(CurrentSaveSlot), 0);
}

void UAaronSaveManagerSubsystem::BeginLoading()
{
	ensureMsgf(CurrentSaveSlot >= 0 && CurrentSaveSlot < MaxSaveSlots, TEXT("CurrentSaveSlot is not set."));
	LoadingSaveGame = Cast<UAaronSaveGame>(UGameplayStatics::LoadGameFromSlot(GetSaveSlotName(CurrentSaveSlot), 0));
	ensureMsgf(LoadingSaveGame, TEXT("Failed to load the SaveGame file."));
	UGameplayStatics::OpenLevel(this, *LoadingSaveGame->SaveInfo.LevelName);
}

void UAaronSaveManagerSubsystem::FinishLoading()
{
	if (LoadingSaveGame)
	{
		ensureMsgf(LoadingSaveGame->LevelName == UGameplayStatics::GetCurrentLevelName(this), TEXT("Tried to FinishLoading a SaveGame that doesn't target the current Level"));

		LoadingSaveGame->Load(this);
		
		//Clean-up the reference (we don't want to load again the next time we switch maps)
		LoadingSaveGame = nullptr;
	}
}