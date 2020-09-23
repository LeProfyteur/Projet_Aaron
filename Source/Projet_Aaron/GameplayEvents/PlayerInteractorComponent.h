// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractorComponent.h"
#include "PlayerInteractorComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class PROJET_AARON_API UPlayerInteractorComponent : public UInteractorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UFUNCTION()
		void OnPlayerInteractionBegin();
	UFUNCTION()
		void OnPlayerInteractionProgress(float Progress);
	UFUNCTION()
		void OnPlayerInteractionCancel();
	UFUNCTION()
		void OnPlayerInteractionComplete();
};
