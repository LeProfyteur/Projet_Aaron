// Fill out your copyright notice in the Description page of Project Settings.


#include "LSDAlteration.h"


#include "Projet_Aaron/Character/AaronCharacter.h"
#include "Projet_Aaron/StatManager/CharacterStatManager.h"

ULSDAlteration::ULSDAlteration()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}

void ULSDAlteration::BeginPlay()
{
	Super::BeginPlay();
	_CreatureStatManager = GetOwner()->FindComponentByClass<UCreatureStatManager>();
	UCharacterStatManager* CharacterStatManager = Cast<UCharacterStatManager>(_CreatureStatManager);

	if (CharacterStatManager)
	{
		AAaronCharacter* Character = Cast<AAaronCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		Character->OnLsdAlteration(TimeMutation);
	}
	_CreatureStatManager->TakeDamage(Damage,0.0f);
}
