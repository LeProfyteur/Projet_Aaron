// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStatManager.h"

bool UCreatureStatManager::ConsumeStamina(float value)
{
	if (Stamina - value < 0)
	{
		return false;
	}
	else
	{
		Stamina -= value;
		return true;
	}
}

void UCreatureStatManager::RecoveryStamina(float value)
{
	if(Stamina + value > StaminaMax)
	{
		Stamina = StaminaMax;
	}
	else
	{
		Stamina += value;
	}
}
