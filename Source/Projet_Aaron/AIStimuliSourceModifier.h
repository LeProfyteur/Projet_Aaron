// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "AIStimuliSourceModifier.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = AI, HideCategories = (Activation, Collision), meta = (BlueprintSpawnableComponent), config = Game)
class PROJET_AARON_API UAIStimuliSourceModifier : public UAIPerceptionStimuliSourceComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TArray<TSubclassOf<UAISense>> GetRegisterSource();

	UFUNCTION(BlueprintCallable)
	void SetRegisterSource(TSubclassOf<UAISense> Sense);
	
};
