// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShapeAlteration.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Engine/World.h"
#include "ParalysisAlteration.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJET_AARON_API UParalysisAlteration : public UShapeAlteration
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UParalysisAlteration();

protected:
	AController* Controller;
	
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
};
