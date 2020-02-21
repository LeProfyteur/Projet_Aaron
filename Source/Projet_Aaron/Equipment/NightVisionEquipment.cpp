// Fill out your copyright notice in the Description page of Project Settings.


#include "NightVisionEquipment.h"

ANightVisionEquipment::ANightVisionEquipment()
{
	PrimaryActorTick.bCanEverTick = false;

	postProcess = CreateDefaultSubobject<UPostProcessComponent>(TEXT("NightVisionProcess"));
	postProcess->SetupAttachment(RootComponent);
}

void ANightVisionEquipment::BeginPlay()
{
	postProcess->Settings.AutoExposureBias = 8;
	postProcess->Settings.SceneColorTint = FLinearColor(0.0f, 10.0f, 0.0f);
}


void ANightVisionEquipment::Activate_Implementation(bool isPressed)
{
	isActivated = !isActivated;
	if (!isActivated)
	{
		postProcess->Settings.bOverride_AutoExposureBias = false;
		postProcess->Settings.bOverride_SceneColorTint = false;
	}
	else
	{
		postProcess->Settings.bOverride_AutoExposureBias = true;
		postProcess->Settings.bOverride_SceneColorTint = true;
	}
}





