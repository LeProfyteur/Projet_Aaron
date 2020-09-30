// Fill out your copyright notice in the Description page of Project Settings.


#include "AaronSpawnPoint.h"
#include "PlayerAdvancementSubsystem.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"

void AAaronSpawnPoint::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (UPlayerAdvancementSubsystem* PlayerAdvancement = GetGameInstance()->GetSubsystem<UPlayerAdvancementSubsystem>())
	{
		PlayerAdvancement->RegisterSpawnPoint(this);
	}
}

void AAaronSpawnPoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UPlayerAdvancementSubsystem* PlayerAdvancement = GetGameInstance()->GetSubsystem<UPlayerAdvancementSubsystem>())
	{
		PlayerAdvancement->UnregisterSpawnPoint(this);
	}

	Super::EndPlay(EndPlayReason);
}

void AAaronSpawnPoint::MakeActive()
{
	if (UPlayerAdvancementSubsystem* PlayerAdvancement = GetGameInstance()->GetSubsystem<UPlayerAdvancementSubsystem>())
	{
		FName CurrentLevelName(*UGameplayStatics::GetCurrentLevelName(this));
		PlayerAdvancement->UpdateSpawnPoint(CurrentLevelName, PlayerStartTag);
	}
}
