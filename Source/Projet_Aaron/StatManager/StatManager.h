// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatChangedEvent, float, Current, float, Max);


UCLASS( meta=(BlueprintSpawnableComponent) )
class PROJET_AARON_API UStatManager : public UActorComponent
{
	GENERATED_BODY()

public:
	/* Events */
	UPROPERTY(BlueprintAssignable)
		FOnStatChangedEvent OnHealthBioChanged;
    UPROPERTY(BlueprintAssignable)
        FOnStatChangedEvent OnHealthTechChanged;

public:
    UFUNCTION(BlueprintCallable, Category = "Damage")
        virtual void TakeDamage(float BioDamage, float TechDamage);
	UFUNCTION(BlueprintCallable, Category = "Damage")
		virtual void Heal(float BioHeal, float TechHeal);
	UFUNCTION(BlueprintCallable, Category = "Damage")
		virtual void Kill();

	/*Getters*/
	UFUNCTION(BlueprintGetter)
		float GetHealthBio() const;
	UFUNCTION(BlueprintGetter)
		float GetHealthBioMax() const;
	UFUNCTION(BlueprintGetter)
		float GetHealthTech() const;
	UFUNCTION(BlueprintGetter)
		float GetHealthTechMax() const;	

	/*Setters*/
	UFUNCTION(BlueprintSetter)
		void SetHealthBio(float NewHealthBio);
	UFUNCTION(BlueprintSetter)
		void SetHealthBioMax(float NewHealthBioMax);
	UFUNCTION(BlueprintSetter)
		void SetHealthTech(float NewHealthTech);
	UFUNCTION(BlueprintSetter)
		void SetHealthTechMax(float NewHealthTechMax);

public:
    UPROPERTY(EditAnywhere, Category = "Health")
        bool DestroyOwnerOnDeath = false;
    UPROPERTY(EditAnywhere, Category = "Health")
		bool Invincible = false;

protected:
    void BeginPlay() override;

    //Life Stat
    UPROPERTY(EditAnywhere, Category = "Health", BlueprintGetter = "GetHealthBio", BlueprintSetter = "SetHealthBio")
        float HealthBio;
    UPROPERTY(EditAnywhere, Category = "Health", BlueprintGetter = "GetHealthBioMax", BlueprintSetter = "SetHealthBioMax")
        float HealthBioMax = 100.0f;
    UPROPERTY(EditAnywhere, Category = "Health", BlueprintGetter = "GetHealthTech", BlueprintSetter = "SetHealthTech")
        float HealthTech;
    UPROPERTY(EditAnywhere, Category = "Health", BlueprintGetter = "GetHealthTechMax", BlueprintSetter = "SetHealthTechMax")
        float HealthTechMax = 100.0f;
};
