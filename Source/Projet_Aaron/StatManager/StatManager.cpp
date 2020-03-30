// Fill out your copyright notice in the Description page of Project Settings.


#include "StatManager.h"



// Sets default values for this component's properties
UStatManager::UStatManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UStatManager::BeginPlay()
{
	Super::BeginPlay();
	HealthBio = HealthBioMax;
	HealthTech = HealthTechMax;
}

FString UStatManager::GetHealthBioRateText() const
{
	TArray<FStringFormatArg> StringArgs {static_cast<int>(HealthBio), static_cast<int>(HealthBioMax)};
	return FString::Format(TEXT("{0} / {1}"), StringArgs);
}

FString UStatManager::GetHealthTechRateText() const
{
	TArray<FStringFormatArg> StringArgs{ static_cast<int>(HealthTech), static_cast<int>(HealthTechMax) };
	return FString::Format(TEXT("{0} / {1}"), StringArgs);
}

void UStatManager::TakeDamage(float BioDamage, float TechDamage)
{
	HealthBio -= BioDamage;
	HealthTech -= TechDamage;


	if(HealthTech <= 0)
	{
		HealthTech = 0;
	}
	
	if(HealthBio <= 0)
	{
		HealthBio = 0;

		Die();
	}

	
}

void UStatManager::Heal(float BioHeal, float TechHeal)
{
	HealthBio += BioHeal;

	if (HealthBio > HealthBioMax)
	{
		HealthBio = HealthBioMax;
	}
	
	HealthTech += TechHeal;

	if(HealthTech > HealthTechMax)
	{
		HealthTech = HealthTechMax;
	}

	
}

void UStatManager::Die()
{
	//GetOwner()->Destroy();
	//Do somethings
}

