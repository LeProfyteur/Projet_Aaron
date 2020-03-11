// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Materials/Material.h"

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
    AMyHUD();
 
	virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void DrawHUD() override;

    UFUNCTION(BlueprintCallable) void UpdateCircleRadius(float RadiusBar);
    UFUNCTION(BlueprintCallable) void ResetCircleRadius();
    UFUNCTION(BlueprintCallable) void GetRadiusCircle(float& Radius);

    UPROPERTY(EditAnywhere) UMaterial* AnalyseMat;
    UPROPERTY(EditAnywhere) UMaterialInstanceDynamic* BarMatInstance;
 
private:
};
