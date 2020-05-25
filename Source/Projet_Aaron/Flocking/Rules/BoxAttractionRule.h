#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Projet_Aaron/Flocking/FlockingRule.h"
#include "BoxAttractionRule.generated.h"

UCLASS()
class PROJET_AARON_API UBoxAttractionRule : public UFlockingRule
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, BlueprintGetter = GetBoxComponent, BlueprintSetter = SetBoxComponent)
		UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
		float MaxForce = 10.0f;
public:

	UFUNCTION(BlueprintSetter)
		void SetBoxComponent(UBoxComponent* InBox);

	UFUNCTION(BlueprintGetter)
		UBoxComponent* GetBoxComponent() const;
	
	void Execute_Implementation(UWorld* World, AFlockAgent* Agent) override;
};