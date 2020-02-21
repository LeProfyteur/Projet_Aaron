// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatManager.h"
#include "CreatureStatManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UCreatureStatManager : public UStatManager
{
	GENERATED_BODY()

protected:

	//Life Stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float StaminaMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float StaminaRecovery;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float BaseSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float ActualSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float ModifSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float JumpForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float JumpStaminaCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float SprintStaminaCost;
	
};
