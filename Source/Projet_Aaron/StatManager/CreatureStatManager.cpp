// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStatManager.h"

UCreatureStatManager::UCreatureStatManager() : Super()
{
	
}

float UCreatureStatManager::GetStamina() const
{
	return Stamina;
}

float UCreatureStatManager::GetStaminaMax() const
{
	return StaminaMax;
}

void UCreatureStatManager::BeginPlay()
{
	Super::BeginPlay();
	
	Stamina = StaminaMax;
	SetJumpForce(JumpForce);
}


void UCreatureStatManager::SetActualSpeed(const float NewSpeed)
{
	ActualSpeed = NewSpeed;
	UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetOwner()->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	CharacterMovementComponent->MaxWalkSpeed = ActualSpeed;
	CharacterMovementComponent->MaxFlySpeed = ActualSpeed;
	CharacterMovementComponent->MaxSwimSpeed = ActualSpeed;
}

void UCreatureStatManager::AddSpeedMultiplier(float Value)
{
	SpeedMultiplier = SpeedMultiplier + Value;
}

/**
 * \brief 
 * \param value Cost of stamina of action to do
 * \return true if can do action else false
 */
bool UCreatureStatManager::ConsumeStamina(float value)
{
	if(bAdrenalineBoost)
	{
		return true;
	}
	else if (Stamina > 0)
	{
        Stamina = FMath::Max(0.0f, Stamina - value);
        OnStaminaChanged.Broadcast(Stamina, StaminaMax);
		return true;
	}
	return false;
}

void UCreatureStatManager::RecoveryStamina(float DeltaTime)
{
	Stamina = FMath::Min(StaminaMax, Stamina + StaminaRecovery);
	OnStaminaChanged.Broadcast(Stamina, StaminaMax);
}

FString UCreatureStatManager::GetStaminaRateText() const
{
	TArray<FStringFormatArg> StringArgs{ static_cast<int>(Stamina), static_cast<int>(StaminaMax) };
	return FString::Format(TEXT("{0} / {1}"), StringArgs);
}

void UCreatureStatManager::SetStamina(const float NewStamina)
{
	Stamina = NewStamina;
	OnStaminaChanged.Broadcast(Stamina, StaminaMax);
}

void UCreatureStatManager::SetStaminaMax(const float NewStaminaMax)
{
    StaminaMax = NewStaminaMax;
	OnStaminaChanged.Broadcast(Stamina, StaminaMax);
}

void UCreatureStatManager::SetJumpForce(const float NewJumpForce)
{
	JumpForce = NewJumpForce;
	UCharacterMovementComponent* CharacterMovement = Cast<UCharacterMovementComponent>(GetOwner()->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	CharacterMovement->JumpZVelocity = JumpForce;
}

void UCreatureStatManager::ResetSpeed()
{
	SetActualSpeed(RunSpeed);
}