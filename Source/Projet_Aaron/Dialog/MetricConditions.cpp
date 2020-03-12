// Fill out your copyright notice in the Description page of Project Settings.


#include "MetricConditions.h"
#include "DialogSubsystem.h"

bool UIsMetricLowerThan::Verify(UObject* WorldContextObject)
{
	return UDialogSubsystem::GetMetric(MetricName) < Value;
}

bool UIsMetricEqual::Verify(UObject* WorldContextObject)
{
	return UDialogSubsystem::GetMetric(MetricName) == Value;
}

bool UIsMetricGreaterThan::Verify(UObject* WorldContextObject)
{
	return UDialogSubsystem::GetMetric(MetricName) > Value;
}
