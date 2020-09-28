// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayEventsSubsystem.h"

//Player Advancement Update Signals
void UGameplayEventsSubsystem::SignalPlayerObjectiveUpdate(FName ObjectiveID)
{
	OnPlayerObjectiveUpdate.Broadcast(ObjectiveID);
}

void UGameplayEventsSubsystem::SignalPlayerScanUpdate(FName ScanID)
{
	OnPlayerScanUpdate.Broadcast(ScanID);
}

void UGameplayEventsSubsystem::SignalPlayerSkillUpdate(FName SkillID)
{
	OnPlayerSkillUpdate.Broadcast(SkillID);
}

void UGameplayEventsSubsystem::SignalPlayerCollectibleUpdate(FName CollectibleID)
{
	OnPlayerCollectibleUpdate.Broadcast(CollectibleID);
}

void UGameplayEventsSubsystem::SignalPlayerLogEntryUpdate(FName LogEntryID)
{
	OnPlayerLogEntryUpdate.Broadcast(LogEntryID);
}

//Player Tutorial Signals
void UGameplayEventsSubsystem::SignalPlayerBeginTutorial()
{
	OnPlayerBeginTutorial.Broadcast();
}

void UGameplayEventsSubsystem::SignalPlayerEndTutorial()
{
	OnPlayerEndTutorial.Broadcast();
}

//Player Queue Tips Signals
void UGameplayEventsSubsystem::SignalPlayerRequestTip(FName TipsID)
{
	OnPlayerRequestTip.Broadcast(TipsID);
}

//Player Inventory Signals
void UGameplayEventsSubsystem::SignalPlayerInventorySlotChanged(int SlotID, FName ItemID)
{
	OnPlayerInventorySlotChanged.Broadcast(SlotID, ItemID);
}

//Player Status Signals
void UGameplayEventsSubsystem::SignalPlayerHealthChanged(float Current, float Max)
{
	OnPlayerHealthChanged.Broadcast(Current, Max);
}

void UGameplayEventsSubsystem::SignalPlayerStaminaChanged(float Current, float Max)
{
	OnPlayerStaminaChanged.Broadcast(Current, Max);
}

void UGameplayEventsSubsystem::SignalPlayerOxygenChanged(float Current, float Max)
{
	OnPlayerOxygenChanged.Broadcast(Current, Max);
}

//Player Scan Signals
void UGameplayEventsSubsystem::SignalPlayerSelectScannableInteractor(UInteractorComponent* Interactor)
{
	OnPlayerSelectScannableInteractor.Broadcast(Interactor);
}

void UGameplayEventsSubsystem::SignalPlayerBeginScan()
{
	OnPlayerBeginScan.Broadcast();
}

void UGameplayEventsSubsystem::SignalPlayerScanProgress(float Progress)
{
	OnPlayerScanProgress.Broadcast(Progress);
}

void UGameplayEventsSubsystem::SignalPlayerCancelScan()
{
	OnPlayerCancelScan.Broadcast();
}
void UGameplayEventsSubsystem::SignalPlayerCompleteScan()
{
	OnPlayerCancelScan.Broadcast();
}


//Action Signals
void UGameplayEventsSubsystem::SignalPlayerSelectActionInteractor(UInteractorComponent* Interactor)
{
	OnPlayerSelectActionInteractor.Broadcast(Interactor);
}

void UGameplayEventsSubsystem::SignalPlayerBeginAction()
{
	OnPlayerBeginAction.Broadcast();
}

void UGameplayEventsSubsystem::SignalPlayerActionProgress(float Progress)
{
	OnPlayerActionProgress.Broadcast(Progress);
}

void UGameplayEventsSubsystem::SignalPlayerCancelAction()
{
	OnPlayerCancelAction.Broadcast();
}

void UGameplayEventsSubsystem::SignalPlayerCompleteAction()
{
	OnPlayerCompleteAction.Broadcast();
}