// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DA_ItemStructure.h"
#include "Interact_Interface.generated.h"

class UDA_SlotStructure;
// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UInteract_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJET_AARON_API IInteract_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		UDA_ItemStructure* Interact();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		UDA_ItemStructure* InteractSafe();
};
