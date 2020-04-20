// Fill out your copyright notice in the Description page of Project Settings.


#include "ParalysisAlteration.h"


UParalysisAlteration::UParalysisAlteration()
{
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = true;
	bAutoRegister = true;
}

void UParalysisAlteration::BeginPlay()
{
	Super::BeginPlay();

	_CreatureStatManager = GetOwner()->FindComponentByClass<UCreatureStatManager>();

	if (_CreatureStatManager)
	{
		_CreatureStatManager->SetSpeedAlteration(true);
	}
	if (Cast<APawn>(GetOwner()))
	{
		Controller = Cast<APawn>(GetOwner())->GetController();
		
		if (Cast<AAIController>(Controller))
			Cast<AAIController>(Controller)->BrainComponent->StopLogic("Paralysed");
		else
			Controller->UnPossess();
	} /*else
	{
		GetOwner()->DisableInput(GetWorld()->GetFirstPlayerController());
	}*/
}

void UParalysisAlteration::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UParalysisAlteration::OnComponentDestroyed(bool bDestroyingHierarchy)
{

	if (Cast<APawn>(GetOwner()))
	{
		if (Cast<AAIController>(Controller))
		{
			//_CreatureStatManager->SetParalysisAlteration(false);
			Cast<AAIController>(Controller)->BrainComponent->ResumeLogic("Unparalysed");
		}
		else
			Controller->Possess(Cast<APawn>(GetOwner()));
	} /*else
	{
		GetOwner()->EnableInput(GetWorld()->GetFirstPlayerController());
	}*/
}