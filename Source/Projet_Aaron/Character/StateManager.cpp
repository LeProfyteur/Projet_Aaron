// Fill out your copyright notice in the Description page of Project Settings.
#include "StateManager.h"

// Sets default values for this component's properties
UStateManager::UStateManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bioLife = maxLife;
	stamina = maxStamina;
	techLife = maxTechLife;
}


// Called when the game starts
void UStateManager::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UStateManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStateManager::Heal(float bioHeal, float techHeal)
{
	bioLife += bioHeal;
	techLife += techHeal;

	if (bioLife > maxLife)
		bioLife = maxLife;
	
	if (techLife > maxTechLife)
		techLife = maxTechLife;
}

void UStateManager::TakeDamage(float bioDamage, float techDamage)
{
	bioLife -= bioDamage;
	techLife -= techDamage;

	if (techLife < 0)
		techLife = 0;

	if (bioLife <= 0)
		Die();
}

void UStateManager::Die()
{
	//Do something
}




