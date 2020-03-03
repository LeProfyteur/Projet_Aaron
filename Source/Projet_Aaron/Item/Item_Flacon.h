// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Item.h"
#include "InterfaceFillSyringe.h"
#include "GameFramework/Actor.h"
#include "Item_Flacon.generated.h"


/**
 * 
 */
UCLASS()
class PROJET_AARON_API AItem_FlaconCPP : public AItem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void UpdateBPFromSyringeTypeCPP(ESyringeType SyringeType);

		bool UseItem_Implementation() override;
};