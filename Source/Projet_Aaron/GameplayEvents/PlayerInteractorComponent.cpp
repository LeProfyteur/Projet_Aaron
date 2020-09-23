// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractorComponent.h"
#include "GameFramework/Actor.h"
#include "GameplayEventsSubsystem.h"


void UPlayerInteractorComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Binding GameplayEventCallbacks"));
	OnInteractionBegin.AddDynamic(this, &UPlayerInteractorComponent::OnPlayerInteractionBegin);
	OnInteractionProgress.AddDynamic(this, &UPlayerInteractorComponent::OnPlayerInteractionProgress);
	OnInteractionCancel.AddDynamic(this, &UPlayerInteractorComponent::OnPlayerInteractionCancel);
	OnInteractionComplete.AddDynamic(this, &UPlayerInteractorComponent::OnPlayerInteractionComplete);
}

void UPlayerInteractorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	OnInteractionBegin.RemoveDynamic(this, &UPlayerInteractorComponent::OnPlayerInteractionBegin);
	OnInteractionProgress.RemoveDynamic(this, &UPlayerInteractorComponent::OnPlayerInteractionProgress);
	OnInteractionCancel.RemoveDynamic(this, &UPlayerInteractorComponent::OnPlayerInteractionCancel);
	OnInteractionComplete.RemoveDynamic(this, &UPlayerInteractorComponent::OnPlayerInteractionComplete);
}

void UPlayerInteractorComponent::OnPlayerInteractionBegin()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling back !"));
	if (UGameplayEventsSubsystem* GameplayEvents = GetOwner()->GetGameInstance()->GetSubsystem<UGameplayEventsSubsystem>())
	{
		GameplayEvents->BroadcastPlayerBeginInteractionEvent();
	}
}

void UPlayerInteractorComponent::OnPlayerInteractionProgress(float Progress)
{
	if (UGameplayEventsSubsystem* GameplayEvents = GetOwner()->GetGameInstance()->GetSubsystem<UGameplayEventsSubsystem>())
	{
		GameplayEvents->BroadcastPlayerInteractionProgressEvent(Progress);
	}
}

void UPlayerInteractorComponent::OnPlayerInteractionCancel()
{
	if (UGameplayEventsSubsystem* GameplayEvents = GetOwner()->GetGameInstance()->GetSubsystem<UGameplayEventsSubsystem>())
	{
		GameplayEvents->BroadcastPlayerCancelInteractionEvent();
	}
}

void UPlayerInteractorComponent::OnPlayerInteractionComplete()
{
	if (UGameplayEventsSubsystem* GameplayEvents = GetOwner()->GetGameInstance()->GetSubsystem<UGameplayEventsSubsystem>())
	{
		GameplayEvents->BroadcastPlayerCompleteInteractionEvent();
	}
}