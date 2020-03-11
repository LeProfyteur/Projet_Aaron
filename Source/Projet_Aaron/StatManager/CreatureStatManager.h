// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "CoreMinimal.h"
#include "StatManager.h"
#include "CreatureStatManager.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJET_AARON_API UCreatureStatManager : public UStatManager
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Walking)
		float RunSpeed = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Walking)
		float WalkSpeed = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Walking)
		float SpeedMultiplier = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Jumping)
		float JumpForce = 600.0f;
	UPROPERTY(BlueprintReadWrite, Category = Stamina)
		float Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float StaminaMax = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float StaminaRecovery = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float JumpStaminaCost = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float SprintStaminaCost = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		bool bAdrenalineBoost;

	UPROPERTY(BlueprintReadWrite)
		float ActualSpeed;

	virtual void BeginPlay() override;

public:

	/*Constructors*/
	UCreatureStatManager();

	/*Getters*/
	UFUNCTION(BlueprintCallable)
		float GetRunSpeed() const { return RunSpeed; }
	UFUNCTION(BlueprintCallable)
		float GetWalkSpeed() const { return WalkSpeed; }
	UFUNCTION(BlueprintCallable)
		float GetSpeedMultiplier() const { return SpeedMultiplier; }
	UFUNCTION(BlueprintCallable)
		float GetStamina() const { return Stamina; }
	UFUNCTION(BlueprintCallable)
		float GetStaminaMax() const { return StaminaMax; }
	UFUNCTION(BlueprintCallable)
		float GetStaminaRecovery() const { return StaminaRecovery; }
	UFUNCTION(BlueprintCallable)
		float GetJumpForce() const { return JumpForce; }
	UFUNCTION(BlueprintCallable)
		float GetJumpStaminaCost() const { return JumpStaminaCost; }
	UFUNCTION(BlueprintCallable)
		float GetSprintStaminaCost() const { return SprintStaminaCost; }
	UFUNCTION(BlueprintCallable)
		float GetStaminaRate() const { return Stamina / StaminaMax; }
	UFUNCTION(BlueprintCallable)
		FString  GetStaminaRateText() const;

	UFUNCTION(BlueprintCallable)
		float GetActualSpeed() const { return ActualSpeed; }

	/*Setters*/
	UFUNCTION(BlueprintCallable)
		void SetStamina(const float NewStamina) { Stamina = NewStamina; }
	UFUNCTION(BlueprintCallable)
		void SetStaminaRecovery(const float NewStaminaRecovery) { StaminaRecovery = NewStaminaRecovery; }
	UFUNCTION(BlueprintCallable)
		void SetStaminaMax(const float NewStaminaMax) { StaminaMax = NewStaminaMax; }
	/**
	 * \brief setup value of bAdrenalineBoost : true if the character don't use any stamina, false otherwise
	 * \param newbAdrenaline new value of bAdrenalineBoost
	 */
	UFUNCTION(BlueprintCallable)
		void SetbAdrenalineBoost(const bool newbAdrenaline) { bAdrenalineBoost = newbAdrenaline; }
	UFUNCTION(BlueprintCallable)
		void SetJumpForce(const float NewJumpForce);
	UFUNCTION(BlueprintCallable)
		void SetJumpStaminaCost(const float NewJumpStaminaCost) { JumpStaminaCost = NewJumpStaminaCost; }
	UFUNCTION(BlueprintCallable)
		void SetSprintStaminaCost(const float NewSprintStaminaCost) { SprintStaminaCost = NewSprintStaminaCost; }

	UFUNCTION(BlueprintCallable)
		void SetActualSpeed(const float NewSpeed);
	
	UFUNCTION(BlueprintCallable)
		void AddSpeedMultiplier(float Value);
	UFUNCTION(BlueprintCallable, Category = "Stamina")
		bool ConsumeStamina(float value);
	UFUNCTION(BlueprintCallable, Category = "Stamina")
		void RecoveryStamina(float DeltaTime);
	UFUNCTION(BlueprintCallable)
		void ResetSpeed();
};
