// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShapeAlteration.h"
#include "Projet_Aaron/StatManager/CreatureStatManager.h"

#include "AdrenalineAlteration.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJET_AARON_API UAdrenalineAlteration : public UShapeAlteration
{
	GENERATED_BODY()


public :

	UAdrenalineAlteration();
	
	virtual void BeginPlay() override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
	
};
