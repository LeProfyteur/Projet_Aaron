// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayEventsSubsystem.h"


void UGameplayEventsSubsystem::BroadcastPlayerHealthChangedEvent(float Current, float Max)
{
	OnPlayerHealthChanged.Broadcast(Current, Max);
}

void UGameplayEventsSubsystem::BroadcastPlayerStaminaChangedEvent(float Current, float Max)
{
	OnPlayerStaminaChanged.Broadcast(Current, Max);
}

void UGameplayEventsSubsystem::BroadcastPlayerOxygenChangedEvent(float Current, float Max)
{
	OnPlayerOxygenChanged.Broadcast(Current, Max);
}

void UGameplayEventsSubsystem::BroadcastPlayerSelectInteractionEvent(AActor* Target)
{
	OnPlayerSelectInteraction.Broadcast(Target);
}

void UGameplayEventsSubsystem::BroadcastPlayerDeselectInteractionEvent(AActor* Target)
{
	OnPlayerDeselectInteraction.Broadcast(Target);
}

void UGameplayEventsSubsystem::BroadcastPlayerBeginInteractionEvent()
{
	OnPlayerBeginInteraction.Broadcast();
}

void UGameplayEventsSubsystem::BroadcastPlayerInteractionProgressEvent(float Progress)
{
	OnPlayerInteractionProgress.Broadcast(Progress);
}

void UGameplayEventsSubsystem::BroadcastPlayerCancelInteractionEvent()
{
	OnPlayerCancelInteraction.Broadcast();
}

void UGameplayEventsSubsystem::BroadcastPlayerCompleteInteractionEvent()
{
	OnPlayerCompleteInteraction.Broadcast();
}