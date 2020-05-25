// Fill out your copyright notice in the Description page of Project Settings.


#include "FlockingRule.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


void UFlockingRule::Execute_Implementation(UWorld* World, AFlockAgent* Agent)
{
}

APlayerController* UFlockingRule::GetPlayerController(UWorld* World, int32 PlayerIndex)
{
	uint32 Index = 0;
	for (FConstPlayerControllerIterator Itr = World->GetPlayerControllerIterator(); Itr; ++Itr)
	{
		APlayerController* PlayerController = Itr->Get();
		if (Index == PlayerIndex)
		{
			return PlayerController;
		}
		Index++;
	}
	
	return nullptr;
}

APawn* UFlockingRule::GetPlayerPawn(UWorld* World, int32 Index)
{
	if (APlayerController* PlayerController = GetPlayerController(World, Index))
	{
		return PlayerController->GetPawn();
	}
	return nullptr;
}