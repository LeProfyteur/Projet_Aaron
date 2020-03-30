// Fill out your copyright notice in the Description page of Project Settings.


#include "AISenseConfig_Smell.h"

UAISenseConfig_Smell::UAISenseConfig_Smell(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DebugColor = FColor::Blue;
	Implementation = GetSenseImplementation();
}

TSubclassOf<UAISense> UAISenseConfig_Smell::GetSenseImplementation() const
{
	return *Implementation;
}
