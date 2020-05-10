// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureStatManager.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"
#include "DetourCrowdAIController.h"
#include "Components/ActorComponent.h"
#include "AIStatManager.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJET_AARON_API UAIStatManager : public UCreatureStatManager
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Perception)
		bool bisDamaged = false;
	UAIStatManager();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Perception)
		float RadiusPercetion = 1500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damages)
		float damagesBio = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damages)
		float damagesTech = 20.0f;
	virtual void BeginPlay() override;

public:
	// Called every frame

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/*Getters*/
	float GetPeripheralVision();
	UFUNCTION(BlueprintCallable)
		float GetDamagesBio();
	UFUNCTION(BlueprintCallable)
		float GetDamagesTech();

	/*Setters*/
	void SetPeripheralVision(float PeripheralVision);

private:
	
	void SetUpRadiusPerception();

};