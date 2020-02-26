// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "CoreMinimal.h"
#include "CreatureStatManager.h"
#include "CharacterStatManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UCharacterStatManager : public UCreatureStatManager
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float DodgeStaminaCost = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float DodgeForce = 2500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterialParameterCollectionInstance* ParameterCollectionInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterialParameterCollection* ParameterCollection;

	virtual void BeginPlay() override;

public:

	/*Contructors*/
	UCharacterStatManager();

	/*Getters*/
	UFUNCTION(BlueprintCallable)
		float GetDodgeStaminaCost() const { return DodgeStaminaCost; }
	UFUNCTION(BlueprintCallable)
		float GetDodgeForce() const { return DodgeForce; }

	/*Setters*/
	UFUNCTION(BlueprintCallable)
		void SetDodgeStaminaCost(float NewDodgeStaminaCost) { DodgeStaminaCost = NewDodgeStaminaCost; }
	UFUNCTION(BlueprintCallable)
		void SetDodgeForce(float NewDodgeForce) { DodgeForce = NewDodgeForce; }

		void TakeDamage(float BioDamage, float TechDamage);
};
