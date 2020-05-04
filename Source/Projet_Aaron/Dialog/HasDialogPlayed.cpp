// Fill out your copyright notice in the Description page of Project Settings.


#include "HasDialogPlayed.h"
#include "Engine/World.h"
#include "DialogSubsystem.h"

bool UHasDialogPlayed::Verify()
{
	UE_LOG(LogTemp, Warning, TEXT("Verify %s"),*DialogName);
	UE_LOG(LogTemp, Warning, TEXT("Value %d"), UDialogSubsystem::GetKnowledge(DialogName) );

	return UDialogSubsystem::GetKnowledge(DialogName) ;
}
