// Fill out your copyright notice in the Description page of Project Settings.


#include "StatManager.h"

float UStatManager::GetHealthBio() const
{
	return HealthBio;
}

float UStatManager::GetHealthBioMax() const
{
	return HealthBioMax;
}
float UStatManager::GetHealthTech() const
{
	return HealthTech;
}

float UStatManager::GetHealthTechMax() const
{
	return HealthTechMax;
}

void UStatManager::SetHealthBio(float NewHealthBio)
{
	HealthBio = FMath::Clamp(NewHealthBio, 0.0f, HealthBioMax);

	if (Invincible && HealthBio <= 0.0f)
	{
		HealthBio = 1;
	}
	
	OnHealthBioChanged.Broadcast(HealthBio, HealthBioMax);

	if (DestroyOwnerOnDeath && HealthBio <= 0.0f)
	{
		GetOwner()->Destroy();
	}
}

void UStatManager::SetHealthBioMax(float NewHealthBioMax)
{
	HealthBioMax = NewHealthBioMax;
    OnHealthBioChanged.Broadcast(HealthBio, HealthBioMax);
}

void UStatManager::SetHealthTech(float NewHealthTech)
{
	HealthTech = FMath::Clamp(NewHealthTech, 0.0f, HealthTechMax);
	OnHealthTechChanged.Broadcast(HealthTech, HealthTechMax);
}

void UStatManager::SetHealthTechMax(float NewHealthTechMax)
{
    HealthTechMax = NewHealthTechMax;
    OnHealthTechChanged.Broadcast(HealthTech, HealthTechMax);
}

void UStatManager::BeginPlay()
{
	Super::BeginPlay();
	HealthBio = HealthBioMax;
	HealthTech = HealthTechMax;
}

void UStatManager::TakeDamage(float BioDamage, float TechDamage)
{
	if (BioDamage > 0)
	{
		SetHealthBio(HealthBio - BioDamage);
	}

	if (TechDamage > 0)
    {
		SetHealthTech(HealthTech - TechDamage);
    }
}

void UStatManager::Heal(float BioHeal, float TechHeal)
{
	if (BioHeal > 0)
	{
		SetHealthBio(HealthBio + BioHeal);
	}

	if (TechHeal > 0)
	{
		SetHealthTech(HealthTech + TechHeal);
	}
}

void UStatManager::Kill()
{
	SetHealthBio(0);
}
