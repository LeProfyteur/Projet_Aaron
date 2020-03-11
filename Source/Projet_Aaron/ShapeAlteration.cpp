// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeAlteration.h"

// Sets default values for this component's properties
UShapeAlteration::UShapeAlteration(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

UShapeAlteration::UShapeAlteration(float const Time_Mutation)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	TimeMutation = Time_Mutation;
	IndexMutation = 0;
}

UShapeAlteration::UShapeAlteration()
{
	TimeMutation = 10.0f;
	IndexMutation = 0;
	PrimaryComponentTick.bCanEverTick = true;
	RegisterComponent();
}

UShapeAlteration::UShapeAlteration(int const Index_Mutation)
{
	TimeMutation = (Index_Mutation + 5.0f)/2.0f;
	IndexMutation = Index_Mutation;
}

UShapeAlteration::UShapeAlteration(float const Time_Mutation,int const Index_Mutation)
{
	TimeMutation = Time_Mutation;
	IndexMutation =Index_Mutation;
}

// Called when the game starts

void UShapeAlteration::BeginPlay()
{
	Super::BeginPlay();
	TimeMutation = 10.0f;
	
	CheckComponent();
}

void UShapeAlteration::CheckComponent()
{
	
	//Protect against Owner-less Calls
	if (!GetOwner()) return;
	
	//Fetch all Components from the Owner
	TArray<UActorComponent*> OwnerComponents;
	GetOwner()->GetComponents(OwnerComponents);
	UClass* SelfClass = GetClass();

	
	for (UActorComponent* Component : OwnerComponents)
	{
		
		//Ignore itself
		if (Component == this)
			continue;
		
		//Ignore if it's not a child of SelfClass
		UClass* CompClass = Component->GetClass();
		if (!CompClass->IsChildOf(SelfClass))
			continue;
		
		//DestroyComponent(GetOwner()->GetComponentByClass(GetClass()));
		Component->DestroyComponent();
		//DestroyComponent(Component);
	}	
}

// Called every frame
void UShapeAlteration::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeMutation -= DeltaTime;

	if (TimeMutation <= 0) 
	{
		DestroyComponent();
	}
	
}