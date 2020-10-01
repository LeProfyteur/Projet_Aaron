// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthChangedEvent, float, CurrentHealth, float, MaxHealth);

UCLASS(meta=(BlueprintSpawnableComponent))
class PROJET_AARON_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void TakeDamage(float Amount);
	UFUNCTION(BlueprintCallable)
		void TakeHeal(float Amount);
	UFUNCTION(BlueprintSetter)
		void SetHealth(float NewHealth);
	UFUNCTION(BlueprintSetter)
		void SetMaxHealth(float NewMaxHealth);

public:
	UPROPERTY(BlueprintAssignable)
		FHealthChangedEvent OnHealthChanged;
protected:
	UPROPERTY(BlueprintReadWrite, BlueprintSetter = SetHealth)
		float Health;
	UPROPERTY(BlueprintReadWrite, BlueprintSetter = SetMaxHealth)
		float MaxHealth;
};