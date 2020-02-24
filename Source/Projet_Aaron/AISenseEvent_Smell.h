// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projet_Aaron/AISense_Smell.h"
#include "Perception/AISenseEvent.h"
#include "AISenseEvent_Smell.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UAISenseEvent_Smell : public UAISenseEvent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	FAISmellEvent Event;

public:
	virtual FAISenseID GetSenseID() const override;

	FORCEINLINE FAISmellEvent& GetSmellEvent()
	{
		Event.Compile();
		return Event;
	}
	
};
