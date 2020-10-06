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

public:
	UPROPERTY(BlueprintAssignable)
		FOnStatChangedEvent OnStaminaChanged;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Walking)
		float RunSpeed = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Walking)
		float WalkSpeed = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Walking)
		float SpeedMultiplier = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Jumping)
		float JumpForce = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina, BlueprintGetter = "GetStamina", BlueprintSetter = "SetStamina")
		float Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina, BlueprintGetter = "GetStaminaMax", BlueprintSetter = "SetStaminaMax")
		float StaminaMax = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float StaminaRecovery = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float JumpStaminaCost = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float SprintStaminaCost = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		bool bAdrenalineBoost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alteration)
		bool HasMudAlteration = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alteration)
		bool HasAdrenalineAlteration = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alteration)
		bool HasSpeedAlteration = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alteration)
		bool HasPoisonAlteration = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alteration)
		bool HasParalysisAlteration = false;

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
	UFUNCTION(BlueprintGetter)
		float GetStamina() const;
	UFUNCTION(BlueprintGetter)
		float GetStaminaMax() const;
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
	UFUNCTION(BlueprintCallable)
		bool GetAdrenalineAlteration() const { return HasAdrenalineAlteration; }
	UFUNCTION(BlueprintCallable)
		bool GetPoisonAlteration() const { return HasPoisonAlteration; }
	UFUNCTION(BlueprintCallable)
		bool GetMudAlteration() const { return HasMudAlteration; }
	UFUNCTION(BlueprintCallable)
		bool GetParalysisAlteration() const { return HasParalysisAlteration; }
	UFUNCTION(BlueprintCallable)
		bool GetSpeedAlteration() const { return HasSpeedAlteration; }

	/*Setters*/
	UFUNCTION(BlueprintSetter)
		void SetStamina(const float NewStamina);
    UFUNCTION(BlueprintSetter)
		void SetStaminaMax(const float NewStaminaMax);
    UFUNCTION(BlueprintCallable)
		void SetStaminaRecovery(const float NewStaminaRecovery) { StaminaRecovery = NewStaminaRecovery; }
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

	UFUNCTION(BlueprintCallable)
		void SetAdrenalineAlteration(bool hasAlteration)  {  HasAdrenalineAlteration = hasAlteration; }
	UFUNCTION(BlueprintCallable)
		void SetPoisonAlteration(bool hasAlteration)  {  HasPoisonAlteration = hasAlteration; }
	UFUNCTION(BlueprintCallable)
		void SetMudAlteration(bool hasAlteration)  {  HasMudAlteration = hasAlteration; }
	UFUNCTION(BlueprintCallable)
		void SetParalysisAlteration(bool hasAlteration)  {  HasParalysisAlteration = hasAlteration; }
	UFUNCTION(BlueprintCallable)
		void SetSpeedAlteration(bool hasAlteration)  {  HasSpeedAlteration = hasAlteration; }
};
