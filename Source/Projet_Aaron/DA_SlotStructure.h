// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_ItemStructure.h"
#include "DA_SlotStructure.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJET_AARON_API UDA_SlotStructure : public UDataAsset
{
	GENERATED_BODY()

public:
	UDA_SlotStructure();
	UDA_SlotStructure(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDA_ItemStructure* ItemStructure;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Quantity;
};
