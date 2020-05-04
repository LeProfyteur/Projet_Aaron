// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AaronSaveGame.h"
#include "AaronSaveManagerSubsystem.generated.h"




/**
 * Subsystem that manages SaveGames using an Index
 */
UCLASS()
class PROJET_AARON_API UAaronSaveManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


private:
	static const int32 MaxSaveSlots;


public:
	UAaronSaveManagerSubsystem();

	/**
	 * Time anchor to compute the playtime when saving
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FDateTime DateBeginPlay;

	/**
	 * Slot Index that targets which slot is selected.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CurrentSaveSlot;

	/**
	 * Reference slot that stores any currently loading SaveGame
	 */
	UPROPERTY(VisibleAnywhere)
		UAaronSaveGame* LoadingSaveGame;

	//PlayTime functions

	UFUNCTION(BlueprintCallable)
		void RefreshDateBeginPlay();

	UFUNCTION(BlueprintCallable)
		FTimespan GetElapsedPlayTime();

	//Save slot manipulation functions//

	UFUNCTION(BlueprintCallable)
		void GetSaveList(TArray<int32>& List);

	UFUNCTION(BlueprintCallable)
		int32 GetEmptySaveSlotIndex();

	UFUNCTION(BlueprintCallable)
		void DeleteGame(int32 SaveSlot);

	UFUNCTION(BlueprintCallable)
		void Save();

	UFUNCTION(BlueprintCallable)
		void BeginLoading();

	UFUNCTION(BlueprintCallable)
		void FinishLoading();

	//Slot to SaveGame filename function
	
	UFUNCTION(BlueprintCallable)
		static FString GetSaveSlotName(int32 SaveSlot);

	UFUNCTION(BlueprintCallable)
		static bool IsSaveSlotValid(int32 SaveSlot);
};