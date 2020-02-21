// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJET_AARON_API UStatManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Life Stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float HealthBio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float HealthBioMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float HealthTech;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float HealthTechMax;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Called when you take damage
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void TakeDamage(float BioDamage, float TechDamage);

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void Die();
	

		
};
