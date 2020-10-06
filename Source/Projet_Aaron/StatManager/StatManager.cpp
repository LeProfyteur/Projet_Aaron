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
	HealthBio = NewHealthBio;
	OnHealthBioChanged.Broadcast(HealthBio, HealthBioMax);
}

void UStatManager::SetHealthBioMax(float NewHealthBioMax)
{
	HealthBioMax = NewHealthBioMax;
    OnHealthBioChanged.Broadcast(HealthBio, HealthBioMax);
}

void UStatManager::SetHealthTech(float NewHealthTech)
{
	HealthTech = NewHealthTech;
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
    if (TechDamage > 0)
    {
        HealthTech = FMath::Max(0.0f, HealthTech - TechDamage);
        OnHealthTechChanged.Broadcast(HealthTech, HealthTechMax);
    }

	if (BioDamage > 0)
	{
		HealthBio = FMath::Max(0.0f, HealthBio - BioDamage);
		
		if (Invinvible && HealthBio < 1)
		{
			HealthBio = 1;
		}

		OnHealthBioChanged.Broadcast(HealthBio, HealthBioMax);

		if (DestroyOwnerOnDeath && HealthBio == 0.0f)
		{
			GetOwner()->Destroy();
		}
	}
}

void UStatManager::Heal(float BioHeal, float TechHeal)
{
    if (BioHeal > 0)
    {
        HealthBio = FMath::Min(HealthBioMax, HealthBio + BioHeal);
        OnHealthBioChanged.Broadcast(HealthBio, HealthBioMax);
    }

    if (TechHeal > 0)
    {
        HealthTech = FMath::Min(HealthTechMax, HealthTech + TechHeal);
        OnHealthTechChanged.Broadcast(HealthTech, HealthTechMax);
    }
}