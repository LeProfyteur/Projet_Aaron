// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Projet_Aaron/DA_ItemStructure.h"
#include "ObjectInteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UObjectInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJET_AARON_API IObjectInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Interact(bool IsPressed,UDA_ItemStructure *ItemStructure,AActor *RefToInteractActor);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		FString GetLabel();
};
