#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlockAgent.generated.h"

class AFlock;

UCLASS()
class PROJET_AARON_API AFlockAgent : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintGetter = GetFlock)
		AFlock* Flock;

	UPROPERTY(BlueprintGetter = GetAgentVelocity)
		FVector AgentVelocity;

	UPROPERTY(BlueprintGetter = GetSteering)
		FVector Steering;

	UPROPERTY()
		USkeletalMeshComponent* SkeletalMeshComponent;
public:
	
	AFlockAgent();

	//Required to reserve the access of SetFlock(AFlock*) to AFlock specifically
protected:
	friend AFlock;
	void SetFlock(AFlock* InFlock);

public:	
	UFUNCTION(BlueprintGetter)
		AFlock* GetFlock() const;

	UFUNCTION(BlueprintGetter)
		FVector GetAgentVelocity() const;

	UFUNCTION(BlueprintGetter)
		FVector GetSteering() const;

	UFUNCTION(BlueprintCallable)
		void AddSteeringForce(const FVector& Force);
	
	virtual void Tick(float DeltaTime) override;
};