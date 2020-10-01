// Fill out your copyright notice in the Description page of Project Settings.


#include "HardBarkEquipment.h"

AHardBarkEquipment::AHardBarkEquipment() : Super() 
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);
	Couldown = MaxCouldown;
}

void AHardBarkEquipment::Activate_Implementation(bool isPressed)
{
	if (isPressed)
	{
		AAaronCharacter* Character = Cast<AAaronCharacter>(GetParentActor());
		if (Character)
		{
//			Character->StatManager->Skills.HardBark = true;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AHardBarkEquipment::StopEffect, TimeActivation, false);
		}
	}
}

void AHardBarkEquipment::StopEffect()
{
	AAaronCharacter* Character = Cast<AAaronCharacter>(GetParentActor());
	if (Character)
	{
//		Character->StatManager->Skills.HardBark = false;
	}
	SetActorTickEnabled(true);
}

void AHardBarkEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Couldown -= DeltaTime;

	if (Couldown <= 0)
	{
		Couldown = MaxCouldown;
		SetActorTickEnabled(false);
	}
}


