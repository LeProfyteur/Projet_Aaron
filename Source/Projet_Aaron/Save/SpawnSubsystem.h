// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SpawnSubsystem.generated.h"

UCLASS()
class PROJET_AARON_API USpawnSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString RespawnLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString RespawnPlayerStartTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString PreferredPlayerStartTag;
};