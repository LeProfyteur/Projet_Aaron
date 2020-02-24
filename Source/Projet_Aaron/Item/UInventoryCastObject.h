// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UInventoryCastObject.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UUInventoryCastObject : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString nameTextItem;
	
};
