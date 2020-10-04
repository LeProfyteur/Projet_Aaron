// Fill out your copyright notice in the Description page of Project Settings.


#include "UseEffect_PutActorOnInstigator.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"


void UUseEffect_PutActorOnInstigator::OnUse_Implementation(AActor* Instigator, UInventoryComponent* UsedInventory, int UsedSlotID, const FName& UsedItemID)
{
	if (IsValid(ActorToSpawn))
	{
		AActor* SpawnedActor = Instigator->GetWorld()->SpawnActor(ActorToSpawn);
		if (USkeletalMeshComponent* SkeletalMeshComponent = Instigator->FindComponentByClass<USkeletalMeshComponent>())
		{
			SpawnedActor->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget,true), SocketName);
		}
	}
}
