// Fill out your copyright notice in the Description page of Project Settings.


#include "HardBarkEquipment.h"

AHardBarkEquipment::AHardBarkEquipment() : Super() {}

void AHardBarkEquipment::Activate_Implementation(bool isPressed)
{
	if (isPressed)
	{
		AAaronCharacter* Character = Cast<AAaronCharacter>(GetParentActor());
		if (Character)
		{
			Character->StatManager->Skills.HardBark = true;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AHardBarkEquipment::StopEffect, TimeActivation, false);
		}
	}
}

void AHardBarkEquipment::StopEffect()
{
	AAaronCharacter* Character = Cast<AAaronCharacter>(GetParentActor());
	if (Character)
	{
		Character->StatManager->Skills.HardBark = false;
	}
}


