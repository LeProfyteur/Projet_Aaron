// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CreatureStatManager.h"
#include "AIStatManager.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJET_AARON_API UAIStatManager : public UCreatureStatManager
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAIStatManager();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Perception)
		float RadiusPercetion = 1500.0f;
	virtual void BeginPlay() override;

public:
	// Called every frame

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/*Getters*/
	float GetPeripheralVision();
	/*Setters*/
	void SetPeripheralVision(float PeripheralVision);

private:
	void SetUpRadiusPerception();

};
