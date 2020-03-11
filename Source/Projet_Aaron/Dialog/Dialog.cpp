// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialog.h"

bool UDialog::IsValid(UObject* WorldContextObject)
{
	for(auto Condition : ListConditions)
	{
		bool Valid = Condition->Verify(WorldContextObject) ^ Condition->Inverted;

		if(Valid == false)
		{
			return false;
		}
	}

	return true;
}
