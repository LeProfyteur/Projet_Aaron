// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DecayingActor.generated.h"

UCLASS()
class PROJET_AARON_API ADecayingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADecayingActor();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeBeforeDestruction = 0.0f;
	
	virtual void Tick(float DeltaTime) override;

};
