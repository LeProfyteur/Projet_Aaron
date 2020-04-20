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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ExposeOnSpawn = true))
		float PoisonDamageBio = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ExposeOnSpawn = true))
		float PoisonDamageTech = 3.0f;
	
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	

	FTimerHandle InputTimeHandle;

private:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Time)
	float TimeAlteration;

	
public:

	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void DamageOverTime();
	
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void TakeDamage();

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

};
