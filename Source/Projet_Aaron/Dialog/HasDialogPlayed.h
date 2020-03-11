// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogCondition.h"
#include "HasDialogPlayed.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UHasDialogPlayed : public UDialogCondition
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, Category = "Condition")
		FString DialogName;
	
	bool Verify(UObject* WorldContextObject) override;
};
