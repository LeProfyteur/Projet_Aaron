// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStatManager.h"

UCreatureStatManager::UCreatureStatManager() : Super()
{
	
}

void UCreatureStatManager::BeginPlay()
{
	Super::BeginPlay();
	
	Stamina = StaminaMax;
	ResetSpeed();
	SetJumpForce(JumpForce);
}



/**
 * \brief 
 * \param value Cost of stamina of action to do
 * \return true if can do action else false
 */
bool UCreatureStatManager::ConsumeStamina(float value)
{
	if (Stamina - value < 0)
	{
		return false;
	}
	else
	{
		Stamina -= value;
		return true;
	}
}

void UCreatureStatManager::RecoveryStamina(float DeltaTime)
{
	if(Stamina + StaminaRecovery * DeltaTime > StaminaMax)
	{
		Stamina = StaminaMax;
	}
	else
	{
		Stamina += StaminaRecovery * DeltaTime;
	}
}

void UCreatureStatManager::SetActualSpeed(const float NewSpeed)
{
	ActualSpeed = NewSpeed;
	UCharacterMovementComponent*CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetOwner()->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	CharacterMovementComponent->MaxWalkSpeed = ActualSpeed;
	CharacterMovementComponent->MaxFlySpeed = ActualSpeed;
	CharacterMovementComponent->MaxSwimSpeed = ActualSpeed;
}

void UCreatureStatManager::SetJumpForce(const float NewJumpForce)
{
	JumpForce = NewJumpForce;
	UCharacterMovementComponent* CharacterMovement = Cast<UCharacterMovementComponent>(GetOwner()->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	CharacterMovement->JumpZVelocity = JumpForce;
}

void UCreatureStatManager::ResetSpeed()
{
	SetActualSpeed(BaseSpeed);
}



