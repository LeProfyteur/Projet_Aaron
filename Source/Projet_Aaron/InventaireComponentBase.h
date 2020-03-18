// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventaireComponent.h"
#include "InventaireComponentBase.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJET_AARON_API UInventaireBaseComponent : public UInventaireComponent
{
	GENERATED_BODY()

public:
	UInventaireBaseComponent();
	void PrepareInventory() override;
	int GetIndexSlot(UDA_ItemStructure* ItemToSearch) override;
	int GetIndexSlotConso(UDA_ItemStructure* ItemToSearch) override;
	int GetIndexSlotSeringue(UDA_ItemStructure* ItemToSearch) override;
};
