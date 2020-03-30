// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DA_SlotStructure.h"
#include "MainHudFixedSizeCPP.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UMainHudFixedSizeCPP : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDA_SlotStructure* ChosenSlot;
	UFUNCTION(BlueprintImplementableEvent)
		void CreateStandartWidgetCPP();
	
};
