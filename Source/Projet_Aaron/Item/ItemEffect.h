// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UseEffect.h"
#include "Animation/AnimMontage.h"
#include "ItemEffect.generated.h"


UCLASS(Blueprintable, EditInlineNew)
class PROJET_AARON_API UItemEffect : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		UAnimMontage* UseAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", Instanced)
		TArray<UUseEffect*> Effects;

public:
	UFUNCTION(BlueprintCallable)
		virtual void Execute(class AActor* Instigator, class UInventoryComponent* UsedInventory, int UsedSlotID, const FName& UsedItemID);
};