// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractorSelector.h"


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

	AActor* TargetActor = nullptr;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility))
	{
		if (Hit.GetActor() != nullptr && Hit.GetActor()->FindComponentByClass<UInteractorComponent>() != nullptr)
		{
			TargetActor = Hit.GetActor();
		}
	}

	UpdateSelectedActor(TargetActor);
}

void UInteractorSelector::TryInteracting()
{
	if (InteractingWithSelection)
	{
		return;
	}

	if (UInteractorComponent* Interactor = GetInteractor())
	{
		Interactor->StartInteraction();
		InteractingWithSelection = Interactor->IsInteracting();
	}
}

void UInteractorSelector::StopInteracting()
{
	if (!InteractingWithSelection)
	{
		return;
	}

	InteractingWithSelection = false;
	if (UInteractorComponent* Interactor = GetInteractor())
	{
		Interactor->StopInteraction();
	}
}



AActor* UInteractorSelector::GetSelectedActor()
{
	return SelectedActor;
}

UInteractorComponent* UInteractorSelector::GetInteractor()
{
	if (SelectedActor != nullptr)
	{
		return SelectedActor->FindComponentByClass<UInteractorComponent>();
	}

	return nullptr;
}

void UInteractorSelector::UpdateSelectedActor(class AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor : %p"), Actor);
	//Skip if nothing happened
	if (SelectedActor == Actor)
	{
		return;
	}

	//Deselection
	if (HasSelection())
	{
		if (InteractingWithSelection)
		{
			StopInteracting();
		}

		OnActorDeselected.Broadcast(SelectedActor);
	}

	SelectedActor = Actor;

	//Selection
	if (HasSelection())
	{
		OnActorSelected.Broadcast(SelectedActor);
	}
}
