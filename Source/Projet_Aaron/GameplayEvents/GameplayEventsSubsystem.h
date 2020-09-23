// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayEventsSubsystem.generated.h"

//Player Status Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayerStatChangedEvent, float, Current, float, Max);

//Interaction Selection Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerSelectInteractionEvent, AActor*, Target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDeselectInteractionEvent, AActor*, Target);

//Interaction Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerBeginInteractionEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerInteractionProgressEvent, float, Progress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerCancelInteractionEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerCompleteInteractionEvent);

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UGameplayEventsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void BroadcastPlayerHealthChangedEvent(float Current, float Max);
	UFUNCTION(BlueprintCallable)
		void BroadcastPlayerStaminaChangedEvent(float Current, float Max);
	UFUNCTION(BlueprintCallable)
		void BroadcastPlayerOxygenChangedEvent(float Current, float Max);
protected:
	UPROPERTY(BlueprintAssignable)
		FPlayerStatChangedEvent OnPlayerHealthChanged;
	UPROPERTY(BlueprintAssignable)
		FPlayerStatChangedEvent OnPlayerStaminaChanged;
	UPROPERTY(BlueprintAssignable)
		FPlayerStatChangedEvent OnPlayerOxygenChanged;


public:
	UFUNCTION(BlueprintCallable)
		void BroadcastPlayerSelectInteractionEvent(AActor* Target);
	UFUNCTION(BlueprintCallable)
		void BroadcastPlayerDeselectInteractionEvent(AActor* Target);
protected:
	UPROPERTY(BlueprintAssignable)
		FPlayerSelectInteractionEvent OnPlayerSelectInteraction;
	UPROPERTY(BlueprintAssignable)
		FPlayerDeselectInteractionEvent OnPlayerDeselectInteraction;


public:
	UFUNCTION(BlueprintCallable)
		void BroadcastPlayerBeginInteractionEvent();
	UFUNCTION(BlueprintCallable)
		void BroadcastPlayerInteractionProgressEvent(float Progress);
	UFUNCTION(BlueprintCallable)
		void BroadcastPlayerCancelInteractionEvent();
	UFUNCTION(BlueprintCallable)
		void BroadcastPlayerCompleteInteractionEvent();
protected:
	UPROPERTY(BlueprintAssignable)
		FPlayerBeginInteractionEvent OnPlayerBeginInteraction;
	UPROPERTY(BlueprintAssignable)
		FPlayerInteractionProgressEvent OnPlayerInteractionProgress;
	UPROPERTY(BlueprintAssignable)
		FPlayerCancelInteractionEvent OnPlayerCancelInteraction;
	UPROPERTY(BlueprintAssignable)
		FPlayerCompleteInteractionEvent OnPlayerCompleteInteraction;
};
