// Fill out your copyright notice in the Description page of Project Settings.


#include "AIStimuliSourceModifier.h"

TArray<TSubclassOf<UAISense>> UAIStimuliSourceModifier::GetRegisterSource() {
	return RegisterAsSourceForSenses;
}


void UAIStimuliSourceModifier::SetRegisterSource(TSubclassOf<UAISense> Sense)
{
	RegisterAsSourceForSenses.Add(Sense);
}
