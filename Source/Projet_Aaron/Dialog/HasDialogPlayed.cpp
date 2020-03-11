// Fill out your copyright notice in the Description page of Project Settings.


#include "HasDialogPlayed.h"
#include "Engine/World.h"
#include "Projet_Aaron/Character/AaronPlayerControllerCPP.h"

bool UHasDialogPlayed::Verify(UObject* WorldContextObject)
{
	return AAaronPlayerControllerCPP::GetKnowledge(WorldContextObject,DialogName) ;
}
