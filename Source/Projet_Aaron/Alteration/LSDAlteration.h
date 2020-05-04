// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShapeAlteration.h"
#include "LSDAlteration.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJET_AARON_API ULSDAlteration : public UShapeAlteration
{
	GENERATED_BODY()

public:
	ULSDAlteration();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ExposeOnSpawn = true))
		float Damage = 5.0f;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
