// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractorComponent.h"

UInteractorComponent::UInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractorComponent::StartInteraction()
{
	if (!CanInteract() || Interacting)
	{
		return;
	}

	//Begin Interaction
	Interacting = true;
	RemainingDuration = InteractionDuration;

	OnInteractionBegin.Broadcast();
}

void UInteractorComponent::StopInteraction()
{
	if (!CanInteract() || !Interacting)
	{
		return;
	}

	//Stop Interaction
	Interacting = false;
	bool Cancelled = !CanInteract() || RemainingDuration > 0;
	RemainingDuration = 0;

	if (Cancelled)
	{
		//There was still some time remaining. Cancel the interaction
		OnInteractionCancel.Broadcast();
	}
	else
	{
		//Interaction has completed when we stopped it.
		OnInteractionComplete.Broadcast();
	}
}


bool UInteractorComponent::IsInteracting()
{
	return Interacting;
}

bool UInteractorComponent::CanInteract()
{
	return bInteractive;
}

void UInteractorComponent::SetInteractive(bool Interactive)
{
	bInteractive = Interactive;
}

void UInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (Interacting)
	{
		if (!CanInteract())
		{
			StopInteraction();
			return;
		}


		// Update Interaction Progress
		RemainingDuration -= DeltaTime;
		RemainingDuration = FMath::Max(0.0f, RemainingDuration);

		//Progression is defaults to 1 for instantaneous Interactions
		float Progression = 1.0f;
		if (InteractionDuration > 0.0f)
		{
			Progression = (InteractionDuration - RemainingDuration) / InteractionDuration;
		}

		OnInteractionProgress.Broadcast(Progression);

		if (RemainingDuration <= 0)
		{
			StopInteraction();
		}
	}
}