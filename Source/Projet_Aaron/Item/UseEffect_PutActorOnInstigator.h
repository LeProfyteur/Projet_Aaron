// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UseEffect.h"
#include "GameFramework/Actor.h"
#include "UseEffect_PutActorOnInstigator.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UUseEffect_PutActorOnInstigator : public UUseEffect
{
	GENERATED_BODY()

public:
	virtual void OnUse_Implementation(AActor* Instigator, UInventoryComponent* UsedInventory, int UsedSlotID, const FName& UsedItemID) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName SocketName;
};
