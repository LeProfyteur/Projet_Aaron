// Fill out your copyright notice in the Description page of Project Settings.
#include "AaronSaveManagerSubsystem.h"
#include "Engine/World.h"
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

bool UAaronSaveManagerSubsystem::IsSaveSlotValid(int32 SaveSlot)
{
	return 0 <= SaveSlot && SaveSlot < MaxSaveSlots;
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
	if (!IsSaveSlotValid(CurrentSaveSlot))
	{
		UE_LOG(LogSerialization, Error, TEXT("Current SaveSlot is not valid (%d). Aborting Save"), CurrentSaveSlot);
		return;
	}

	UAaronSaveGame* SaveGame = Cast<UAaronSaveGame>(UGameplayStatics::CreateSaveGameObject(UAaronSaveGame::StaticClass()));

	SaveGame->Save(this);
	
	UGameplayStatics::SaveGameToSlot(SaveGame, GetSaveSlotName(CurrentSaveSlot), 0);
}

void UAaronSaveManagerSubsystem::BeginLoading()
{
	if (!IsSaveSlotValid(CurrentSaveSlot))
	{
		UE_LOG(LogSerialization, Error, TEXT("Current SaveSlot is not valid (%d). Aborting Load"), CurrentSaveSlot);
		return;
	}

	LoadingSaveGame = Cast<UAaronSaveGame>(UGameplayStatics::LoadGameFromSlot(GetSaveSlotName(CurrentSaveSlot), 0));

	if (!LoadingSaveGame)
	{
		UE_LOG(LogSerialization, Error, TEXT("Failed to load the AaronSaveGame. Aborting Load."));
		return;
	}

	UGameplayStatics::OpenLevel(this, *LoadingSaveGame->SaveInfo.LevelName);
}

void UAaronSaveManagerSubsystem::FinishLoading()
{
	//Check if there is a SaveGame currently loading.
	if (LoadingSaveGame)
	{
		//Load the SaveGame.
		LoadingSaveGame->Load(this);

		//Reset the Reference.
		LoadingSaveGame = nullptr;
	}
}