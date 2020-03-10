// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogCondition.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew)
class PROJET_AARON_API UDialogCondition : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Condition")
		bool Inverted;

	UFUNCTION(BlueprintCallable)
		virtual bool Verify();
};
