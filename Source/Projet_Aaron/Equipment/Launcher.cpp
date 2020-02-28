// Fill out your copyright notice in the Description page of Project Settings.


#include "Launcher.h"

ALauncher::ALauncher() : Super()
{
	// Create the point to spawn the projectile from
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Projectile spawn point"));
	SphereComponent->SetGenerateOverlapEvents(false);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetupAttachment(RootComponent);

	Aiming = false;
	ReadyToFire = true;
}

void ALauncher::Activate_Implementation(bool isPressed)
{
	if (ProjectileClass->IsValidLowLevel() && !isPressed && ReadyToFire)
	{
		FVector loc = SphereComponent->GetComponentLocation();
		FRotator rota = SphereComponent->GetComponentRotation();
		GetWorld()->SpawnActor(ProjectileClass, &loc, &rota);
		Aiming = false;
		ReadyToFire = false;
		GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &ALauncher::CooldownReady, Cooldown, false);
	}
}

void ALauncher::CooldownReady()
{
	ReadyToFire = true;
}
