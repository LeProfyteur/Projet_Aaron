// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MotionControllerComponent.h"
#include "ClimbableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UClimbableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJET_AARON_API IClimbableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Climb(UMotionControllerComponent* MotionController);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void LetGo(UMotionControllerComponent* MotionController);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void GetGripPoint(FVector& GripPoint);
};
