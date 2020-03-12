// Fill out your copyright notice in the Description page of Project Settings.


#include "MetricConditions.h"
#include "DialogSubsystem.h"

bool UIsMetricLowerThan::Verify()
{
	return UDialogSubsystem::GetMetric(MetricName) < Value;
}

bool UIsMetricEqual::Verify()
{
	return UDialogSubsystem::GetMetric(MetricName) == Value;
}

bool UIsMetricGreaterThan::Verify()
{
	return UDialogSubsystem::GetMetric(MetricName) > Value;
}
