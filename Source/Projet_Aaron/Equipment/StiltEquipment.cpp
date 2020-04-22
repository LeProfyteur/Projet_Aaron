// Fill out your copyright notice in the Description page of Project Settings.


#include "StiltEquipment.h"

AStiltEquipment::AStiltEquipment()
{
	timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine"));
	updateHeightFunction.BindUFunction(this, FName("UpdateHeight"));
}

void AStiltEquipment::Activate_Implementation(bool isPressed)
{
	if (isPressed)
	{
		ACharacter* Character = GetWorld()->GetFirstPlayerController()->GetCharacter();
		if (!isActivate)
		{
			Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
			StartPos = Character->GetActorLocation();
			timeline->PlayFromStart();
		}
		else
		{
			timeline->ReverseFromEnd();
			Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		}
		isActivate = !isActivate;
	}
}

void AStiltEquipment::OnEquip_Implementation(FCharacterSkills& Skills)
{
	Skills.Stilt = true;
}

void AStiltEquipment::OnUnequip_Implementation(FCharacterSkills& Skills)
{
	Skills.Stilt = false;
}

void AStiltEquipment::UpdateHeight(float value)
{
	ACharacter* Character = GetWorld()->GetFirstPlayerController()->GetCharacter();
	Character->SetActorLocation(StartPos + FVector(0, 0, value * Height));
}

void AStiltEquipment::BeginPlay()
{
	Super::BeginPlay();

	if (FloatHeightCurve)
	{
		timeline->SetTimelineLength(1.5f);
		timeline->AddInterpFloat(FloatHeightCurve, updateHeightFunction);
	}
}


