// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrapplePointer.generated.h"

UCLASS()
class PROJET_AARON_API AGrapplePointer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrapplePointer();

	USphereComponent* SphereBox;

};
