// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Kismet/KismetMathLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"

#include "CoreMinimal.h"
#include "IKLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UIKLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "IK")
		static FVector TraceGround(UObject* Target, const FVector& From, float RaycastMaxDistance);

	UFUNCTION(BlueprintCallable, Category = "IK")
		static void TraceGroundWithNormal(UObject* Target, const FVector& From, float RaycastMaxDistance, FVector &HitPoint, FVector &Normal);

	UFUNCTION(BlueprintCallable, Category = "IK")
		static FRotator BodyRotateIK(UObject* Target, ACharacter* Character, float DistanceFromCenterFront, float DistanceFromCenterBack);

	UFUNCTION(BlueprintCallable, Category = "IK")
		static float BodyHipsIK(UObject* Target, ACharacter* Character, FRotator BodyRotate, float SizeOfLeg);

	UFUNCTION(BlueprintCallable, Category = "IK")
		static void FootByGroupIK(UObject* Target, ACharacter* Character, const TArray<FName> &ListSocketName, float DistanceMaxGround, TArray<float> &IKLegs, float &HipDeplacement, TArray<FRotator> &RotateFoot);

	UFUNCTION(BlueprintCallable, Category = "IK")
		static bool IsGrounded(UObject* Target, ACharacter* Character);
};
