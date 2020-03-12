// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogCondition.h"
#include "MetricConditions.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UIsMetricLowerThan : public UDialogCondition
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Condition")
	FString MetricName;

	UPROPERTY(EditAnywhere, Category = "Condition")
	int32 Value;

	virtual bool Verify() override;
};


UCLASS()
class PROJET_AARON_API UIsMetricEqual : public UDialogCondition
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Condition")
	FString MetricName;

	UPROPERTY(EditAnywhere, Category = "Condition")
	int32 Value;

	virtual bool Verify() override;

};


UCLASS()
class PROJET_AARON_API UIsMetricGreaterThan : public UDialogCondition
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Condition")
	FString MetricName;

	UPROPERTY(EditAnywhere, Category = "Condition")
	int32 Value;

	virtual bool Verify() override;

};
