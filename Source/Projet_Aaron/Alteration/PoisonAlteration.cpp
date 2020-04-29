// Fill out your copyright notice in the Description page of Project Settings.


#include "PoisonAlteration.h"

#include "Projet_Aaron/Character/AaronCharacter.h"

// Sets default values for this component's properties
UPoisonAlteration::UPoisonAlteration()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UPoisonAlteration::BeginPlay()
{
	Super::BeginPlay();
	MaxTimeAlteration = TimeMutation;
	TimeAlteration = TimeMutation;
	_CreatureStatManager = GetOwner()->FindComponentByClass<UCreatureStatManager>();
	CharacterStatManager = Cast<UCharacterStatManager>(_CreatureStatManager);

	if (CharacterStatManager)
	{
		CharacterStatManager->SetPoisonAlteration(true);
		CharacterStatManager->SetPoisonEffect(1.0f);
		DamageOverTime();
	}
	else if (_CreatureStatManager)
	{
		_CreatureStatManager->SetPoisonAlteration(true);
		DamageOverTime();
	}

	AAaronCharacter* Character = Cast<AAaronCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Character->OnPoisonAlteration();
	
}

// Called every frame
void UPoisonAlteration::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//if (CharacterStatManager)
	//{
	//	CharacterStatManager->SetPoisonEffect(TimeMutation / MaxTimeAlteration);
	//	//UE_LOG(LogActor, Error, TEXT("%f / %f = %f"), TimeMutation, MaxTimeAlteration, TimeMutation / MaxTimeAlteration);
	//}
}

void UPoisonAlteration::DamageOverTime()
{
	UWorld* World = GetWorld();
	World->GetTimerManager().SetTimer(InputTimeHandle, this, &UPoisonAlteration::TakeDamage, 1.0f, true, 0.5f);
	_CreatureStatManager->TakeDamage(PoisonDamageBio, PoisonDamageTech);
}


void UPoisonAlteration::TakeDamage()
{
	if (TimeAlteration <= 1.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(InputTimeHandle);
		/*if (CharacterStatManager)
		{
			CharacterStatManager->SetPoisonEffect(0.0f);
		}*/
	}
	
	TimeAlteration -= 1.0f;
	_CreatureStatManager->TakeDamage(PoisonDamageBio, PoisonDamageTech);
}

void UPoisonAlteration::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	if (_CreatureStatManager)
	{
		_CreatureStatManager->SetPoisonAlteration(false);
	}
}
