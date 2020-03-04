// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "ShapeAlteration.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJET_AARON_API UShapeAlteration : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	//Constructor
	UShapeAlteration();
	UShapeAlteration(float const Time_Mutation);
	UShapeAlteration(int const Index_Mutation);
	UShapeAlteration(float const Time_Mutation, int const Index_Mutation);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Called in BeginPlay to updat e component if the owner already have it
	virtual void CheckComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Time)
		float TimeMutation;

	//Mutation Event
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Event)
		int IndexMutation;

	
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
};
