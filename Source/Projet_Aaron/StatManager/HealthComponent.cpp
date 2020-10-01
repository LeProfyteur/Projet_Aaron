// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


void UHealthComponent::TakeDamage(float Amount)
{
	if (Amount > 0)
	{
		Health = FMath::Max(0.0f, Health - Amount);
		OnHealthChanged.Broadcast(Health, MaxHealth);
	}
}

void UHealthComponent::TakeHeal(float Amount)
{
	if (Amount > 0)
	{
		Health = FMath::Min(MaxHealth, Health + Amount);
		OnHealthChanged.Broadcast(Health, MaxHealth);
	}
}

void UHealthComponent::SetHealth(float NewHealth)
{
	Health = NewHealth;
	OnHealthChanged.Broadcast(Health, MaxHealth);
}

void UHealthComponent::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
	OnHealthChanged.Broadcast(Health, MaxHealth);	
}