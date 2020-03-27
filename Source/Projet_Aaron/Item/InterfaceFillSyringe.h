// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Item.h"
#include "InterfaceFillSyringe.generated.h"

UENUM(BlueprintType)
enum ESyringeType
{
	ST_Antipoison UMETA(DisplayName = "AntiPoison"),
	ST_Adrenaline UMETA(DisplayName = "Adrenaline"),
	ST_Vie UMETA(DisplayName = "Vie"),
	ST_Tech UMETA(DisplayName = "Tech"),
	ST_AntiRadiation UMETA(DisplayName = "AntiRadiation"),
	ST_None UMETA(DisplayName = "None"),
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfaceFillSyringe : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJET_AARON_API IInterfaceFillSyringe
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		ESyringeType GetSeringueType();
};
