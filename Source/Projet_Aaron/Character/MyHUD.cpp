// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"

AMyHUD::AMyHUD()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	AnalyseMat = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), nullptr, TEXT("/Game/Projet_Aaron/CC/CircularBar.CircularBar")));
	
	BarMatInstance = UMaterialInstanceDynamic::Create(AnalyseMat, this);
	BarMatInstance->SetScalarParameterValue(FName(TEXT("Decimal")), 0.0f);
	BarMatInstance->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(0.7f, 200.0f, 0.34f));

	SetActorTickEnabled(false);
}

void AMyHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	FVector2D viewportSize(0, 0);
	GEngine->GameViewport->GetViewportSize(viewportSize);
	
	DrawMaterialSimple(BarMatInstance, viewportSize.X / 2.0f, viewportSize.Y / 2.0f, 50.0f, 50.0f);
}

void AMyHUD::UpdateCircleRadius(float RadiusBar)
{
	BarMatInstance->SetScalarParameterValue(FName("Decimal"), RadiusBar);
}

void AMyHUD::ResetCircleRadius()
{
	SetActorTickEnabled(false);
	BarMatInstance->SetScalarParameterValue(FName(TEXT("Decimal")), 0.0f);
}

void AMyHUD::GetRadiusCircle(float& Radius)
{
	BarMatInstance->GetScalarParameterValue(FName("Decimal"), Radius);
}




