// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Flacon.h"
#include "Projet_Aaron/Character/FPS_Character.h"

bool AItem_FlaconCPP::UseItem_Implementation()
{
	UE_LOG(LogActor, Warning, TEXT("FlaconCPP::UseItem"));
	FHitResult OutHit;
	//APawn* character = GetWorld()->GetFirstPlayerController()->GetPawn();
	AFPS_Character* Character = Cast<AFPS_Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
	FVector Start = Character->FpsCamera->GetComponentLocation();
	FVector End = Start + Character->FpsCamera->GetForwardVector() * Character->RaycastDistanceInventory;
	FCollisionQueryParams collisionParams;

	if (GetWorld()->SweepSingleByChannel(OutHit, Start, End, Character->FpsCamera->GetComponentRotation().Quaternion(), ECC_Visibility, FCollisionShape::MakeCapsule(50, 50), collisionParams))
	{
		if (OutHit.GetActor()->Implements<UInterfaceFillSyringe>())
		{
			ESyringeType Syringe = IInterfaceFillSyringe::Execute_GetSeringueType(OutHit.GetActor());
			UpdateBPFromSyringeTypeCPP(Syringe);
			return true;
		}
	}
	return false;
}
