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

	if (Cast<APawn>(GetOwner()))
	{
		Controller = Cast<APawn>(GetOwner())->GetController();
		
		if (Cast<AAIController>(Controller))
			Cast<AAIController>(Controller)->BrainComponent->StopLogic("Paralysed");
		else if (Cast<APlayerController>(Controller))
			GetOwner()->DisableInput(Cast<APlayerController>(Controller));
	}
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
			Cast<AAIController>(Controller)->BrainComponent->RestartLogic();
		else if (Cast<APlayerController>(Controller))
			GetOwner()->EnableInput(Cast<APlayerController>(Controller));
	}
}