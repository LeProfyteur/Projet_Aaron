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
	BarMatInstance->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(0.9f, 0.9f, 0.9f));

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
	
	DrawMaterialSimple(BarMatInstance, (viewportSize.X / 2.0f)-40.0f, (viewportSize.Y / 2.0f)-40.0f, 80.0f, 80.0f);

	//FString text = "Pourcent";
	//DrawText(text, FLinearColor(1, 1, 1, 1), (viewportSize.X / 2.0f) - 40.0f, (viewportSize.Y / 2.0f) - 20.0f,0,1.0f);
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




