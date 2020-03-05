// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeAlteration.h"

// Sets default values for this component's properties
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
	// ...
	
}


// Called every frame
void UShapeAlteration::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...

	TimeMutation -= DeltaTime;

	if (TimeMutation <= 0) 
	{
		DestroyComponent();
	}
	
}









