// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialog.h"

bool UDialog::IsValid()
{
	for(auto Condition : ListConditions)
	{
		bool Valid = Condition->Verify() ^ Condition->Inverted;

		if(Valid == false)
		{
			return false;
		}
	}

	return true;
}
