#pragma once

#include "CoreMinimal.h"
#include "Projet_Aaron/Flocking/FlockingRule.h"
#include "CollisionAvoidanceRule.generated.h"

UCLASS()
class PROJET_AARON_API UCollisionAvoidanceRule : public UFlockingRule
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float MaxDistance = 100.0f;

	UPROPERTY(EditAnywhere)
		float MaxForce = 10.0f;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<ECollisionChannel> CollisionChannel = ECC_Visibility;

	void Execute_Implementation(UWorld* World, AFlockAgent* Agent) override;
};
