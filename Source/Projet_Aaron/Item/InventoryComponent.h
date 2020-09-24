// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInventorySlotChanged, int, SlotID, int, ItemID);


UCLASS( meta=(BlueprintSpawnableComponent) )
class PROJET_AARON_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()		
};
