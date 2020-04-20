// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../StatManager/CreatureStatManager.h"
#include "ShapeAlteration.h"
#include "SpeedAlteration.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJET_AARON_API USpeedAlteration : public UShapeAlteration
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpeedAlteration();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Time, meta = (ExposeOnSpawn = true))
		float SpeedReduction = -0.9f;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	FTimerHandle InputTimeHandle;

private:
	float TimeAlteration;
	
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*UFUNCTION(BlueprintCallable, Category = "Speed")
		void ReductionSpeed();
	*/
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
};
