// Fill out your copyright notice in the Description page of Project Settings.


#include "AaronGameMode.h"

#include "Projet_Aaron/Progression/PlayerAdvancementSubsystem.h"
#include "Engine/GameInstance.h"

AActor* AAaronGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("AAaronGameMode::ChoosePlayerStart_Implementation"));
	if (UPlayerAdvancementSubsystem* PlayerAdvancement = GetGameInstance()->GetSubsystem<UPlayerAdvancementSubsystem>())
	{
		return PlayerAdvancement->GetSpawnPoint();
	}
	return nullptr;
}
