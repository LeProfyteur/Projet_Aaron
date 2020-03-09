// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "AIStimuliSmellComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = AI, HideCategories = (Activation, Collision), meta = (BlueprintSpawnableComponent), config = Game)
class PROJET_AARON_API UAIStimuliSmellComponent : public UAIPerceptionStimuliSourceComponent
{
	GENERATED_BODY()
	
};
