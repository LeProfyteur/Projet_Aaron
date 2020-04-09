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
		FRotator rota;
		
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayConnected())
		{
			rota = SphereComponent->GetComponentRotation();
		}
		else
		{
			FHitResult HitResult;
			FVector Start;
			FVector End;
			FVector TargetPosition;
			Start = SphereComponent->GetComponentLocation();
			AAaronCharacter* c = Cast<AAaronCharacter>(GetParentActor());
			End = Start + c->FpsCamera->GetForwardVector() * Distance;

			GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

			if (HitResult.IsValidBlockingHit())
				TargetPosition = HitResult.ImpactPoint;
			else
				TargetPosition = End;

			FVector Forward = TargetPosition - SphereComponent->GetComponentLocation();
			rota = UKismetMathLibrary::MakeRotFromXZ(Forward, FVector::UpVector);
		}
		
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
