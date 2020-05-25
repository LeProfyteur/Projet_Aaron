#pragma once

#include "CoreMinimal.h"
#include "Projet_Aaron/Flocking/FlockingRule.h"
#include "FlockSeparationRule.generated.h"

UCLASS()
class PROJET_AARON_API UFlockSeparationRule : public UFlockingRule
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		float MaxDistance = 100.0f;

	UPROPERTY(EditAnywhere)
		float MaxForce = 10.0f;

	void Execute_Implementation(UWorld* World, AFlockAgent* Agent) override;
};
