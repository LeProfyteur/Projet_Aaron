// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogCondition.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Dialog.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJET_AARON_API UDialog : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Dialog")
		TArray<UDialogCondition*> ListConditions;

	UPROPERTY(EditAnywhere, Category = "Dialog")
		UBehaviorTree* DialogBehaviourTree;

	UFUNCTION(BlueprintCallable)
		bool IsValid();
	
};
