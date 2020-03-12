// Fill out your copyright notice in the Description page of Project Settings.


#include "HasDialogPlayed.h"
#include "Engine/World.h"
#include "Projet_Aaron/Character/AaronPlayerControllerCPP.h"
#include "DialogSubsystem.h"

bool UHasDialogPlayed::Verify()
{
	return UDialogSubsystem::GetKnowledge(DialogName) ;
}
