// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvironmentalScanEquipment.h"

AEnvironmentalScanEquipment::AEnvironmentalScanEquipment() : Super()
{
	timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine"));
	updateRadiusFunction.BindUFunction(this, FName("UpdateRadius"));
	updateHighlightFunction.BindUFunction(this, FName("UpdateHighlight"));
	FinishTimeLIneFunction.BindUFunction(this, FName("FinishTimeline"));
}

void AEnvironmentalScanEquipment::Activate_Implementation(bool isPressed)
{
	if (isPressed && timeline)
		timeline->PlayFromStart();
}

void AEnvironmentalScanEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnvironmentalScanEquipment::UpdateRadius(float value)
{
	ParameterCollectionInstance->SetScalarParameterValue(FName(TEXT("Radius")), value);
}

void AEnvironmentalScanEquipment::UpdateHighlight(float value)
{
	ParameterCollectionInstance->SetScalarParameterValue(FName(TEXT("Highlight")), value);
}

void AEnvironmentalScanEquipment::FinishTimeline()
{
	ParameterCollectionInstance->SetScalarParameterValue(FName(TEXT("Highlight")), 0.0f);
	ParameterCollectionInstance->SetScalarParameterValue(FName(TEXT("Radius")), 0.0f);
}

void AEnvironmentalScanEquipment::BeginPlay()
{
	Super::BeginPlay();

	if(FloatHighlightCurve && FloatRadiusCurve && ParameterCollection)
	{
		ParameterCollectionInstance = GetWorld()->GetParameterCollectionInstance(ParameterCollection);

		timeline->SetTimelineLength(5.0f);
		timeline->AddInterpFloat(FloatRadiusCurve, updateRadiusFunction);
		timeline->AddInterpFloat(FloatHighlightCurve, updateHighlightFunction);
		timeline->SetTimelineFinishedFunc(FinishTimeLIneFunction);
	}
}








