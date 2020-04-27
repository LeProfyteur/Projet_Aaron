// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatManager.h"

UCharacterStatManager::UCharacterStatManager() : Super()
{
	static ConstructorHelpers::FObjectFinder<UMaterialParameterCollection> ParamCol(TEXT("/Game/Projet_Aaron/PostProcessingEffect/Helper/MPC_PostProcessing.MPC_PostProcessing"));
	if (ParamCol.Succeeded())
		ParameterCollection = ParamCol.Object;

	Skills = FCharacterSkills();
	Oxygene = OxygeneMax;
}

void UCharacterStatManager::BeginPlay()
{
	Super::BeginPlay();
	ParameterCollectionInstance = GetWorld()->GetParameterCollectionInstance(ParameterCollection);
}


void UCharacterStatManager::TakeDamage(float BioDamage, float TechDamage)
{
	if (!Skills.HardBark)
		Super::TakeDamage(BioDamage, TechDamage);

	float RateHealth = (HealthBio+HealthTech) / (HealthBioMax+HealthTechMax);
	if(RateHealth <= 0.5f)
	{
		ParameterCollectionInstance->SetScalarParameterValue(FName(TEXT("Damage")), 1.0f - RateHealth);
	}
}

void UCharacterStatManager::ConsumeOxygene(float OxygeneToConsume)
{
	if (Oxygene - OxygeneToConsume < 0.0f)
		TakeDamage(OxygeneToConsume, 0.0f);
	else
		Oxygene -= OxygeneToConsume;
}

void UCharacterStatManager::RecoveryOxygene(float DeltaTime)
{
	Oxygene += 10.0f * DeltaTime;
	if (Oxygene > OxygeneMax)
		Oxygene = OxygeneMax;
}

void UCharacterStatManager::Heal(float BioHeal, float TechHeal)
{
	Super::Heal(BioHeal, TechHeal);
	//remove des post process
	float RateHealth = (HealthBio + HealthTech) / (HealthBioMax + HealthTechMax);
	if (RateHealth <= 0.5f)
	{
		ParameterCollectionInstance->SetScalarParameterValue(FName(TEXT("Damage")), 1.0f - RateHealth);
	}else
	{
		ParameterCollectionInstance->SetScalarParameterValue(FName(TEXT("Damage")), 0.0f);
	}
}

float UCharacterStatManager::GetNightVisionEffect()
{
	float Res;
	ParameterCollectionInstance->GetScalarParameterValue(FName("NightVision"), Res);
	return Res;
}

void UCharacterStatManager::SetNightVisionEffect(float Value)
{
	ParameterCollectionInstance->SetScalarParameterValue(FName(TEXT("NightVision")), Value);
}

void UCharacterStatManager::SetPoisonEffect(float Value)
{
	ParameterCollectionInstance->SetScalarParameterValue(FName(TEXT("Poison")), Value);
}
