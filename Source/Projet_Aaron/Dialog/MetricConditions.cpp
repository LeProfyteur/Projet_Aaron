// Fill out your copyright notice in the Description page of Project Settings.


#include "MetricConditions.h"
#include "DialogSubsystem.h"

bool UIsMetricLowerThan::Verify()
{
	UE_LOG(LogTemp, Warning, TEXT("Verify %s"), MetricName);
	UE_LOG(LogTemp, Warning, TEXT("Value %b"), UDialogSubsystem::GetMetric(MetricName) );

	return UDialogSubsystem::GetMetric(MetricName) < Value;
}

bool UIsMetricEqual::Verify()
{
	UE_LOG(LogTemp, Warning, TEXT("Verify %s"), MetricName);
	UE_LOG(LogTemp, Warning, TEXT("Value %b"), UDialogSubsystem::GetMetric(MetricName) );

	return UDialogSubsystem::GetMetric(MetricName) == Value;
}

bool UIsMetricGreaterThan::Verify()
{
	UE_LOG(LogTemp, Warning, TEXT("Verify %s"), MetricName);
	UE_LOG(LogTemp, Warning, TEXT("Value %b"), UDialogSubsystem::GetMetric(MetricName) );

	return UDialogSubsystem::GetMetric(MetricName) > Value;
}
