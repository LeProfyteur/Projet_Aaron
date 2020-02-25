// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
		float DodgeStaminaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float DodgeForce;

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
};
