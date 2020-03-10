// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatManager.h"

UCharacterStatManager::UCharacterStatManager() : Super()
{
	static ConstructorHelpers::FObjectFinder<UMaterialParameterCollection> ParamCol(TEXT("/Game/Projet_Aaron/PostProcessingEffect/Helper/MPC_PostProcessing.MPC_PostProcessing"));
	if (ParamCol.Succeeded())
		ParameterCollection = ParamCol.Object;
}

void UCharacterStatManager::BeginPlay()
{
	Super::BeginPlay();
	ParameterCollectionInstance = GetWorld()->GetParameterCollectionInstance(ParameterCollection);
}


void UCharacterStatManager::TakeDamage(float BioDamage, float TechDamage)
{
	Super::TakeDamage(BioDamage, TechDamage);

	float RateHealth = HealthBio / HealthBioMax;
	if(RateHealth <= 0.5f)
	{
		ParameterCollectionInstance->SetScalarParameterValue(FName(TEXT("Damage")), 1.0f - RateHealth);
	}
}