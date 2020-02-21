// Fill out your copyright notice in the Description page of Project Settings.


#include "AISenseEvent_Smell.h"

FAISenseID UAISenseEvent_Smell::GetSenseID() const
{
	return UAISense::GetSenseID<UAISense_Smell>();
}
