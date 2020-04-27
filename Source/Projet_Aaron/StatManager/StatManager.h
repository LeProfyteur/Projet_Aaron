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
	UPROPERTY(BlueprintReadWrite, Category = Health)
	float HealthBio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float HealthBioMax = 100.0f;
	UPROPERTY(BlueprintReadWrite, Category = Health)
	float HealthTech;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float HealthTechMax = 100.0f;
	
public:	

	/*Getters*/
	UFUNCTION(BlueprintCallable)
		float GetHealthBio() const { return HealthBio; }
	UFUNCTION(BlueprintCallable)
		float GetHealthBioMax() const { return HealthBioMax; }
	UFUNCTION(BlueprintCallable)
		float GetHealthTech() const { return HealthTech; }
	UFUNCTION(BlueprintCallable)
		float GetHealthTechMax() const { return HealthTechMax; }
	UFUNCTION(BlueprintCallable)
		float GetHealthBioRate() const { return HealthBio / HealthBioMax; }
	UFUNCTION(BlueprintCallable)
		FString GetHealthBioRateText() const;
	UFUNCTION(BlueprintCallable)
		float GetHealthTechRate() const { return HealthTech / HealthTechMax; }

	UFUNCTION(BlueprintCallable)
		float GetHealthRate() const { return (HealthBio + HealthTech) / (HealthBioMax + HealthTechMax); }
	UFUNCTION(BlueprintCallable)
		FString GetHealthTechRateText() const;
	


	/*Setters*/
	UFUNCTION(BlueprintCallable)
		void SetHealthBio(float NewHealthBio) { HealthBio = NewHealthBio; }
	UFUNCTION(BlueprintCallable)
		void SetHealthBioMax(float NewHealthBioMax) { HealthBioMax = NewHealthBioMax; }
	UFUNCTION(BlueprintCallable)
		void SetHealthTech(float NewHealthTech) { HealthTech = NewHealthTech; }
	UFUNCTION(BlueprintCallable)
		void SetHealthTechMax(float NewHealthTechMax) { HealthBio = NewHealthTechMax; }
	
	//Called when you take damage
	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual void TakeDamage(float BioDamage, float TechDamage);

	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual void Heal(float BioHeal, float TechHeal);

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void Die();
};
