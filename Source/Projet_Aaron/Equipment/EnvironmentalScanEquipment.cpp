// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvironmentalScanEquipment.h"

AEnvironmentalScanEquipment::AEnvironmentalScanEquipment()
{
	PrimaryActorTick.bCanEverTick = false;

	timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine"));
	updateRadiusFunction.BindUFunction(this, FName("UpdateTimeLineRadius"));
	updateHighlightFunction.BindUFunction(this, FName("UpdateTimeLineHighlight"));

	static ConstructorHelpers::FObjectFinder<UCurveFloat> RadiusCurve(TEXT("/Game/RadiusCurve.RadiusCurve"));
	if(RadiusCurve.Succeeded())
		FloatRadiusCurve = RadiusCurve.Object;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> HighlightCurve(TEXT("/Game/HightlightCurve.HightlightCurve"));
	if(HighlightCurve.Succeeded())
		FloatHighlightCurve = HighlightCurve.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialParameterCollection> ParamCol(TEXT("/Game/Projet_Aaron/CC/EnvironmentScanParams.EnvironmentScanParams"));
	if(ParamCol.Succeeded())
		ParameterCollection = ParamCol.Object;
	
}

void AEnvironmentalScanEquipment::Activate_Implementation(bool isPressed)
{
	if (isPressed && timeline)
	{
		UE_LOG(LogActor, Error, TEXT("dans le activate"));
		//timeline->PlayFromStart();
		TSet<UCurveBase*> mycurves;
		timeline->GetAllCurves(mycurves);
		
		for(UCurveBase* curve : mycurves)
		{
			UE_LOG(LogActor, Error, TEXT("%s : %f"), *curve->GetName());
		}
		UE_LOG(LogActor, Error, TEXT("%f"), timeline->GetPlayRate());
	}
}

void AEnvironmentalScanEquipment::OnEquip_Implementation()
{
	
}

void AEnvironmentalScanEquipment::OnUnequip_Implementation()
{
	
}

void AEnvironmentalScanEquipment::Tick(float DeltaTime)
{
	
}

void AEnvironmentalScanEquipment::UpdateTimeLineRadius(float value)
{
	UE_LOG(LogActor, Error, TEXT("SA update"));
	ParameterCollectionInstance->SetScalarParameterValue(FName(TEXT("Radius")), value);
}

void AEnvironmentalScanEquipment::UpdateTimeLineHighlight(float value)
{
	ParameterCollectionInstance->SetScalarParameterValue(FName(TEXT("Highlight")), value);
}


void AEnvironmentalScanEquipment::BeginPlay()
{
	ParameterCollectionInstance = GetWorld()->GetParameterCollectionInstance(ParameterCollection);
	
	timeline->SetTimelineLength(5.0f);
	timeline->AddInterpFloat(FloatRadiusCurve, updateRadiusFunction);
	timeline->AddInterpFloat(FloatHighlightCurve, updateHighlightFunction);
}








