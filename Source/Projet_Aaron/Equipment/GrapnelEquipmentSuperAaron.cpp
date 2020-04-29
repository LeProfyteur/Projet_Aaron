// Fill out your copyright notice in the Description page of Project Settings.


#include "GrapnelEquipmentSuperAaron.h"
#include "Projet_Aaron/Character/AaronCharacter.h"

// Sets default values
AGrapnelEquipmentSuperAaron::AGrapnelEquipmentSuperAaron()
{
	PrimaryActorTick.bCanEverTick = false;
	SetActorEnableCollision(false);

	RootComponent = StaticMeshComponent;

	timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine"));
	updateFunction.BindUFunction(this, FName("TimelineCallback"));

	hookMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hook Mesh"));
	hookMeshComponent->SetupAttachment(RootComponent);

	cable = CreateDefaultSubobject<UCableComponent>(TEXT("Cable"));
	cable->SetupAttachment(RootComponent);

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser System"));
	ParticleSystem->SetupAttachment(RootComponent);
}

void AGrapnelEquipmentSuperAaron::BeginPlay()
{
	Super::BeginPlay();

	timeline->SetTimelineLength(5.0f);
	timeline->SetTimelinePostUpdateFunc(updateFunction);
	timeline->SetLooping(true);

	cable->SetHiddenInGame(true, false);
}

void AGrapnelEquipmentSuperAaron::Activate_Implementation(bool isPressed)
{
	if (isPressed)
	{
		if (!IsValid(myBullet) && canHook)
		{
			ParticleSystem->Activate();
			foundHookSpot = false;
			PlayTimeline();
		}
	}
	else
	{
		ParticleSystem->DeactivaateNextTick();
		if (foundHookSpot && canHook)
		{
			DisableInput(GetWorld()->GetFirstPlayerController());
			canHook = false;
			playTLForLaser = false;
			cable->SetHiddenInGame(false, false);
			hookMeshComponent->SetHiddenInGame(true);
			myBullet = GetWorld()->SpawnActor<AGrappleHead>(hookMeshComponent->GetComponentLocation(), GetActorRotation());
			myBullet->locationToGo = locationToGrip;
			cable->SetAttachEndTo(myBullet, NAME_None, NAME_None);
			Hook();
		}
	}
}

void AGrapnelEquipmentSuperAaron::TimelineCallback()
{
	FHitResult outHit;
	FVector vStart;
	FVector vEnd;
	FCollisionQueryParams collisionParams(FName(TEXT("Laser")), false, this);

	if (playTLForLaser)
	{
		vStart = StaticMeshComponent->GetComponentLocation();
		ParticleSystem->SetBeamSourcePoint(0, vStart, 0);
		AAaronCharacter* c = Cast<AAaronCharacter>(GetParentActor());
		vEnd = vStart + c->FpsCamera->GetForwardVector() * Distance;

		bool haveHit = GetWorld()->LineTraceSingleByChannel(outHit, vStart, vEnd, ECC_Visibility, collisionParams);
		if (haveHit && outHit.Actor->GetClass()->ImplementsInterface(UHookInterface::StaticClass()))
		{
			ParticleSystem->SetColorParameter(FName("color"), FLinearColor::Green);
			locationToGrip = outHit.Location;
			TimeInterpolation = (outHit.Distance * 0.25f) / 250.0f;
			foundHookSpot = true;
		}
		else
		{
			ParticleSystem->SetColorParameter(FName("color"), FLinearColor::Red);
			if (haveHit)
				locationToGrip = outHit.Location;
			else
				locationToGrip = outHit.TraceEnd;

			foundHookSpot = false;
		}
		ParticleSystem->SetBeamTargetPoint(0, locationToGrip, 0);
	}
}

void AGrapnelEquipmentSuperAaron::PlayTimeline()
{
	if (timeline)
	{
		timeline->Play();
	}
}

void AGrapnelEquipmentSuperAaron::Hook()
{
	cable->SetAttachEndTo(myBullet, NAME_None, NAME_None);
	cable->SetVisibility(true);
	FLatentActionInfo LatentActionInfo = FLatentActionInfo(1, 1, TEXT("AfterHook"), this);
	ACharacter* Character = GetWorld()->GetFirstPlayerController()->GetCharacter();
	UKismetSystemLibrary::MoveComponentTo(Character->GetRootComponent(), locationToGrip, Character->GetActorRotation(), true, false, TimeInterpolation, false, EMoveComponentAction::Move, LatentActionInfo);
}

void AGrapnelEquipmentSuperAaron::AfterHook()
{
	cable->SetHiddenInGame(true, true);
	if (IsValid(myBullet))
	{
		myBullet->Destroy();
		myBullet = nullptr;
		hookMeshComponent->SetHiddenInGame(false, true);
		foundHookSpot = false;
		playTLForLaser = true;
		canHook = true;
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}