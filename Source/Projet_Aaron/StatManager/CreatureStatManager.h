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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float StaminaMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float StaminaRecovery;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Speed)
		float BaseSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Speed)
		float ActualSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Speed)
		float ModifSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Speed)
		float JumpForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float JumpStaminaCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float SprintStaminaCost;

public:

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	bool ConsumeStamina(float value);
	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void RecoveryStamina(float value);
	
};
