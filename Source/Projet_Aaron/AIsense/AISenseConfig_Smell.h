// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AISense_Smell.h"
#include "CoreMinimal.h"
#include "Perception/AISenseConfig.h"
#include "AISense_Smell.h"
#include "AISenseConfig_Smell.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "AI Smell Config"))
class PROJET_AARON_API UAISenseConfig_Smell : public UAISenseConfig
{
	GENERATED_BODY()

public:

	/*The class reference which contains the logic for this sense config */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sense", NoClear, config)
		TSubclassOf<UAISense_Smell> Implementation;

	/* The radius around the pawn that we're checking for "water resources" */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sense", config, meta = (UIMin = 0.0, ClampMin = 0.0))
		float PhobiaRadius;

	/* True if you want to display the debug sphere around the pawn */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sense", config)
		bool bDisplayDebugSphere;

	UAISenseConfig_Smell(const FObjectInitializer& ObjectInitializer);

	/* The editor will call this when we're about to assign an implementation for this config */
	virtual TSubclassOf<UAISense> GetSenseImplementation() const override;
};
