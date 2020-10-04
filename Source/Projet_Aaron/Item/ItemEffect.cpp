	// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemEffect.h"
#include "GameFramework/Actor.h"
#include "InventoryComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"


void UItemEffect::Execute(AActor* Instigator, UInventoryComponent* UsedInventory, int UsedSlotID, const FName& UsedItemID)
{
	//Safely try to trigger the UseAnimation Montage
	if (UseAnimation)
	{
		if (USkeletalMeshComponent* SkeletalMeshComponent = Instigator->FindComponentByClass<USkeletalMeshComponent>())
		{
			if (UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance())
			{
				AnimInstance->Montage_Play(UseAnimation);
			}
		}
	}

	//Invoke all the effects
	for (UUseEffect* Effect : Effects)
	{
		if (Effect)
		{
			Effect->OnUse(Instigator, UsedInventory, UsedSlotID, UsedItemID);
		}
	}
}
