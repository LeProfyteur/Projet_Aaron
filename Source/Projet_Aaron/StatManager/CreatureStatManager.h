// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
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
	UPROPERTY(BlueprintReadWrite, Category = Stamina)
		float Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float StaminaMax = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float StaminaRecovery = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Speed)
		float BaseSpeed = 600.0f;
	UPROPERTY(BlueprintReadWrite, Category = Speed)
		float ActualSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Speed)
		float JumpForce = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float JumpStaminaCost = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float SprintStaminaCost = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Speed)
		float SprintSpeed = 1200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Speed)
		float CrouchSpeed = 300.0f;

	virtual void BeginPlay() override;

public:

	/*Constructors*/
	UCreatureStatManager();

	/*Getters*/
	UFUNCTION(BlueprintCallable)
		float GetStamina() const { return Stamina; }
	UFUNCTION(BlueprintCallable)
		float GetStaminaMax() const { return StaminaMax; }
	UFUNCTION(BlueprintCallable)
		float GetStaminaRecovery() const { return StaminaRecovery; }
	UFUNCTION(BlueprintCallable)
		float GetBaseSpeed() const { return BaseSpeed; }
	UFUNCTION(BlueprintCallable)
		float GetActualSpeed() const { return ActualSpeed; }
	UFUNCTION(BlueprintCallable)
		float GetJumpForce() const { return JumpForce; }
	UFUNCTION(BlueprintCallable)
		float GetJumpStaminaCost() const { return JumpStaminaCost; }
	UFUNCTION(BlueprintCallable)
		float GetSprintStaminaCost() const { return SprintStaminaCost; }
	UFUNCTION(BlueprintCallable)
		float GetSprintSpeed() const { return SprintSpeed; }
	UFUNCTION(BlueprintCallable)
		float GetCrouchSpeed() const { return SprintStaminaCost; }

	/*Setters*/
	UFUNCTION(BlueprintCallable)
		void SetStamina(const float NewStamina) { Stamina = NewStamina; }
	UFUNCTION(BlueprintCallable)
		void SetStaminaRecovery(const float NewStaminaRecovery) { StaminaRecovery = NewStaminaRecovery; }
	UFUNCTION(BlueprintCallable)
		void SetStaminaMax(const float NewStaminaMax) { StaminaMax = NewStaminaMax; }
	UFUNCTION(BlueprintCallable)
		void SetActualSpeed(const float NewSpeed);
	UFUNCTION(BlueprintCallable)
		void SetJumpForce(const float NewJumpForce);
	UFUNCTION(BlueprintCallable)
		void SetJumpStaminaCost(const float NewJumpStaminaCost) { JumpStaminaCost = NewJumpStaminaCost; }
	UFUNCTION(BlueprintCallable)
		void SetSprintStaminaCost(const float NewSprintStaminaCost) { SprintStaminaCost = NewSprintStaminaCost; }
	
	
	UFUNCTION(BlueprintCallable, Category = "Stamina")
		bool ConsumeStamina(float value);
	UFUNCTION(BlueprintCallable, Category = "Stamina")
		void RecoveryStamina(float DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "Speed")
		void ResetSpeed();
	
};
