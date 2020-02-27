// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Curves/CurveBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "CoreMinimal.h"
#include "EquipmentBase.h"
#include "EnvironmentalScanEquipment.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API AEnvironmentalScanEquipment : public AEquipmentBase
{
	GENERATED_BODY()

public :

	AEnvironmentalScanEquipment();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UCurveFloat* FloatRadiusCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UCurveFloat* FloatHighlightCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UTimelineComponent* timeline;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterial* environmentalScanMat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterialInstanceDynamic* environmentalScanMatInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterialParameterCollectionInstance* ParameterCollectionInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterialParameterCollection* ParameterCollection;

	UFUNCTION()
		void UpdateRadius(float value);

	UFUNCTION()
		void UpdateHighlight(float value);

	UFUNCTION()
		void FinishTimeline();
	
	virtual void Activate_Implementation(bool isPressed) override;
	virtual void OnEquip_Implementation() override;
	virtual void OnUnequip_Implementation() override;

	virtual void Tick(float DeltaTime) override;

protected:
	FOnTimelineFloat updateRadiusFunction{};
	FOnTimelineFloat updateHighlightFunction{};
	FOnTimelineEvent FinishTimeLIneFunction{};

	virtual void BeginPlay() override;
	
};
