// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShapeAlteration.h"
#include "Projet_Aaron/StatManager/StatManager.h"
#include "TimerManager.h"
#include "PoisonAlteration.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJET_AARON_API UPoisonAlteration : public UShapeAlteration
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPoisonAlteration();
	
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	//UFUNCTION(BlueprintCallable, Category = "Damage")
	float PoisonDamageBio;
	float PoisonDamageTech;
	
	UPROPERTY() UStatManager* _statManager;

	FTimerHandle InputTimeHandle;

private:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Time)
	float TimeAlteration;

	
public:

	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void DamageOverTime();
	UFUNCTION()
	void TakeDamage();

		
};
