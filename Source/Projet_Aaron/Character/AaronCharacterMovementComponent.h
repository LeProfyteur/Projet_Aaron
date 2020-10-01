// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AaronCharacterMovementComponent.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Crouch UMETA(DisplayName = "Crouch"),
	Walk UMETA(DisplayName = "Walk"),
	Run UMETA(DisplayName = "Run"),
	Dash UMETA(DisplayName = "Dash"),
	Slide UMETA(DisplayName = "Slide"),
	Swim UMETA(DisplayName = "Swim"),
	Crawl UMETA(DisplayName = "Crawl"),
	InAir UMETA(DisplayName = "InAir"),
	Glide UMETA(DisplayName = "Glide"),
	Climb UMETA(DisplayName = "Climb"),
};

UCLASS()
class PROJET_AARON_API UAaronCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
};
