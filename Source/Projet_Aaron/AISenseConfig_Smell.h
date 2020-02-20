// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AISenseConfig.h"
#include "Projet_Aaron/AISense_Smell.h"
#include "AISenseConfig_Smell.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UAISenseConfig_Smell : public UAISenseConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sense", NoClear, config)
	TSubclassOf<UAISense_Smell> Implementation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sense", NoClear, config, meta = (UIMin = 0.0, ClampMin = 0.0))
	float SmellingRange;

	UAISenseConfig_Smell(const FObjectInitializer& ObjectInitializer);

	TSubclassOf<UAISense> GetSenseImplementation() const override;
};
