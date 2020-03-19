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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Walking)
		float SprintSpeed = 800.0f;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crouching)
		float CrouchSpeed = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crouching)
		float CrouchWalkSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Swimming)
		float SwimmingSpeed = 350.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Swimming)
		float SwimmingSprintSpeed = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sliding)
		float SlideForce = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sliding)
		float SlideStopVelocity = 25.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dodging)
		float DodgeStaminaCost = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dodging)
		float DodgeForce = 2500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Climbing)
		float ClimbSpeed = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Climbing)
		float ClimbRange = 400.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Oxygene)
		float Oxygene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Oxygene)
		float OxygeneMax = 60.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Jump)
		float MaxJumpMulti = 3.0f;

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
	UFUNCTION(BlueprintCallable)
		float GetSprintSpeed() const { return SprintSpeed; }
	UFUNCTION(BlueprintCallable)
		float GetCrouchRunSpeed() const { return CrouchSpeed; }
	UFUNCTION(BlueprintCallable)
		float GetCrouchWalkSpeed() const { return CrouchWalkSpeed; }
	UFUNCTION(BlueprintCallable)
		float GetSwimmingSpeed() const { return SwimmingSpeed; }
	UFUNCTION(BlueprintCallable)
		float GetSwimmingSprintSpeed() const { return SwimmingSprintSpeed; }
	UFUNCTION(BlueprintCallable)
		float GetClimbRange() const { return ClimbRange; }
	UFUNCTION(BlueprintCallable)
		float GetClimbSpeed() const { return ClimbSpeed; }
	UFUNCTION(BlueprintCallable)
		float GetSlideForce() const { return SlideForce; }
	UFUNCTION(BlueprintCallable)
		float GetSlideStopVelocity() const { return SlideStopVelocity; }
	UFUNCTION(BlueprintCallable)
		float GetOxygeneRate() const { return Oxygene / OxygeneMax; }

	/*Setters*/
	UFUNCTION(BlueprintCallable)
		void SetDodgeStaminaCost(float NewDodgeStaminaCost) { DodgeStaminaCost = NewDodgeStaminaCost; }
	UFUNCTION(BlueprintCallable)
		void SetDodgeForce(float NewDodgeForce) { DodgeForce = NewDodgeForce; }

		void TakeDamage(float BioDamage, float TechDamage);

		void ConsumeOxygene(float OxygeneToConsume);

		void RecoveryOxygene(float DeltaTime);
};
