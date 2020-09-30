// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AaronGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API AAaronGameMode : public AGameMode
{
	GENERATED_BODY()

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
};
