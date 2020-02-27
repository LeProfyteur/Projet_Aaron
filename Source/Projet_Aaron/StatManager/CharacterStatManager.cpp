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

	float rateHealth = HealthBio / HealthBioMax;
	if(rateHealth <= 0.5f)
	{
		UE_LOG(LogActor, Error, TEXT("%f"), 1.0f - rateHealth);
		ParameterCollectionInstance->SetScalarParameterValue(FName(TEXT("Damage")), 1.0f - rateHealth);
	}
}


