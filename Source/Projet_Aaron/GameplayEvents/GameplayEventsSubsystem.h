// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InteractorComponent.h"
#include "GameplayEventsSubsystem.generated.h"

//Player Advancement Update Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerAdvancementUpdateEvent, FName, AdvancementID);

//Player Tutorial Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerTutorialEvent);

//Player Tips Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerRequestTipEvent, FName, TipsID);

//Player Inventory Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayerInventorySlotChangedEvent, int, SlotID, FName, ItemID);

//Player Status Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayerStatChangedEvent, float, Current, float, Max);

//Player Scan Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerSelectScannableInteractorEvent, UInteractorComponent*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerBeginScanEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerScanProgressEvent, float, Progress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerCancelScanEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerCompleteScanEvent);

//Action Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerSelectActionInteractorEvent, UInteractorComponent*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerBeginActionEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerActionProgressEvent, float, Progress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerCancelActionEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerCompleteActionEvent);

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UGameplayEventsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	//Player Advancement Update Signals
	UFUNCTION(BlueprintCallable)
		void SignalPlayerObjectiveUpdate(FName ObjectiveID);
	UFUNCTION(BlueprintCallable)
		void SignalPlayerScanUpdate(FName ScanID);
	UFUNCTION(BlueprintCallable)
		void SignalPlayerSkillUpdate(FName SkillID);
	UFUNCTION(BlueprintCallable)
		void SignalPlayerCollectibleUpdate(FName CollectibleID);
	UFUNCTION(BlueprintCallable)
		void SignalPlayerLogEntryUpdate(FName LogEntryID);
	
    //Player Tutorial Signals
    UFUNCTION(BlueprintCallable)
        void SignalPlayerBeginTutorial();
    UFUNCTION(BlueprintCallable)
        void SignalPlayerEndTutorial();

	//Player Queue Tips Signals
	UFUNCTION(BlueprintCallable)
		void SignalPlayerRequestTip(FName TipsID);
	
	//Player Inventory Signals
	UFUNCTION(BlueprintCallable)
		void SignalPlayerInventorySlotChanged(int SlotID, FName ItemID);

	//Player Status Signals
	UFUNCTION(BlueprintCallable)
		void SignalPlayerHealthChanged(float Current, float Max);
	UFUNCTION(BlueprintCallable)
		void SignalPlayerStaminaChanged(float Current, float Max);
	UFUNCTION(BlueprintCallable)
		void SignalPlayerOxygenChanged(float Current, float Max);

	//Player Scan Signals
	UFUNCTION(BlueprintCallable)
		void SignalPlayerSelectScannableInteractor(UInteractorComponent* Interactor);
	UFUNCTION(BlueprintCallable)
		void SignalPlayerBeginScan();
	UFUNCTION(BlueprintCallable)
		void SignalPlayerScanProgress(float Progress);
	UFUNCTION(BlueprintCallable)
		void SignalPlayerCancelScan();
	UFUNCTION(BlueprintCallable)
		void SignalPlayerCompleteScan();


	//Action Signals
	UFUNCTION(BlueprintCallable)
		void SignalPlayerSelectActionInteractor(UInteractorComponent* Interactor);
	UFUNCTION(BlueprintCallable)
		void SignalPlayerBeginAction();
	UFUNCTION(BlueprintCallable)
		void SignalPlayerActionProgress(float Progress);
	UFUNCTION(BlueprintCallable)
		void SignalPlayerCancelAction();
	UFUNCTION(BlueprintCallable)
		void SignalPlayerCompleteAction();
	
protected:
	//Player Advancement Update Events
	UPROPERTY(BlueprintAssignable)
		FPlayerAdvancementUpdateEvent OnPlayerObjectiveUpdate;
	UPROPERTY(BlueprintAssignable)
		FPlayerAdvancementUpdateEvent OnPlayerScanUpdate;
	UPROPERTY(BlueprintAssignable)
		FPlayerAdvancementUpdateEvent OnPlayerSkillUpdate;
	UPROPERTY(BlueprintAssignable)
		FPlayerAdvancementUpdateEvent OnPlayerCollectibleUpdate;
	UPROPERTY(BlueprintAssignable)
		FPlayerAdvancementUpdateEvent OnPlayerLogEntryUpdate;

    //Player Tutorial Events
    UPROPERTY(BlueprintAssignable)
        FPlayerTutorialEvent OnPlayerBeginTutorial;
    UPROPERTY(BlueprintAssignable)
        FPlayerTutorialEvent OnPlayerEndTutorial;

	//Player Tips Events
	UPROPERTY(BlueprintAssignable)
		FPlayerRequestTipEvent OnPlayerRequestTip;
	
	//Player Inventory Events
	UPROPERTY(BlueprintAssignable)
		FPlayerInventorySlotChangedEvent OnPlayerInventorySlotChanged;
	
	//Player Status Events
	UPROPERTY(BlueprintAssignable)
		FPlayerStatChangedEvent OnPlayerHealthChanged;
	UPROPERTY(BlueprintAssignable)
        FPlayerStatChangedEvent OnPlayerStaminaChanged;
    UPROPERTY(BlueprintAssignable)
        FPlayerStatChangedEvent OnPlayerOxygenChanged;
    UPROPERTY(BlueprintAssignable)
        FPlayerStatChangedEvent OnPlayerPoisonIntensityChanged;
    UPROPERTY(BlueprintAssignable)
        FPlayerStatChangedEvent OnPlayerHallucinationIntensityChanged;

	//Player Scan Events
	UPROPERTY(BlueprintAssignable)
		FPlayerSelectScannableInteractorEvent OnPlayerSelectScannableInteractor;
	UPROPERTY(BlueprintAssignable)
		FPlayerBeginScanEvent OnPlayerBeginScan;
	UPROPERTY(BlueprintAssignable)
		FPlayerScanProgressEvent OnPlayerScanProgress;
	UPROPERTY(BlueprintAssignable)
		FPlayerCancelScanEvent OnPlayerCancelScan;
	UPROPERTY(BlueprintAssignable)
		FPlayerCompleteScanEvent OnPlayerCompleteScan;

	//Action Events
	UPROPERTY(BlueprintAssignable)
		FPlayerSelectActionInteractorEvent OnPlayerSelectActionInteractor;
	UPROPERTY(BlueprintAssignable)
		FPlayerBeginActionEvent OnPlayerBeginAction;
	UPROPERTY(BlueprintAssignable)
		FPlayerActionProgressEvent OnPlayerActionProgress;
	UPROPERTY(BlueprintAssignable)
		FPlayerCancelActionEvent OnPlayerCancelAction;
	UPROPERTY(BlueprintAssignable)
		FPlayerCompleteActionEvent OnPlayerCompleteAction;
};
