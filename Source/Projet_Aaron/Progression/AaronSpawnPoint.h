// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "AaronSpawnPoint.generated.h"

UCLASS()
class PROJET_AARON_API AAaronSpawnPoint : public APlayerStart
{
	GENERATED_BODY()

protected:
	virtual void PostInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable)
		void MakeActive();
};
