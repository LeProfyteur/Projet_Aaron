// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractorSelector.h"
#include "InteractorComponent.h"
#include "Engine/World.h"


UInteractorSelector::UInteractorSelector()
{
	PrimaryComponentTick.bCanEverTick = true;
	DebugArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DebugArrow"));
}

void UInteractorSelector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * Range;
	FHitResult Hit;

	UInteractorComponent* Selection = nullptr;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility))
	{
		if (Hit.GetActor() != nullptr)
		{
			Selection = static_cast<UInteractorComponent*>( Hit.GetActor()->GetComponentByClass(InteractorTypeFilter) );
		}
	}
	UpdateSelection(Selection);
}


void UInteractorSelector::StartInteraction()
{
	if (SelectedInteractor)
	{
		SelectedInteractor->StartInteraction();
	}
}

void UInteractorSelector::StopInteraction()
{
	if (SelectedInteractor)
	{
		SelectedInteractor->StopInteraction();
	}
}

bool UInteractorSelector::IsInteracting()
{
	return SelectedInteractor && SelectedInteractor->IsInteracting();
}

UInteractorComponent* UInteractorSelector::GetSelectedInteractor()
{
	return SelectedInteractor;
}


void UInteractorSelector::UpdateSelection(UInteractorComponent* NewSelection)
{
	//Skip if nothing happened
	if (SelectedInteractor != NewSelection)
	{
		//Deselection
		if (SelectedInteractor)
		{
			if (IsInteracting())
			{
				StopInteraction();
			}
			
			OnInteractorDeselected.Broadcast(SelectedInteractor);
		}

		SelectedInteractor = NewSelection;

		//Selection
		if (SelectedInteractor)
		{
			OnInteractorSelected.Broadcast(SelectedInteractor);
		}
	}
}
