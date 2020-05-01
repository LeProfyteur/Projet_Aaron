// Fill out your copyright notice in the Description page of Project Settings.


#include "GrapnelEquipmentSuperAaron.h"
#include "Projet_Aaron/Character/AaronCharacter.h"

// Sets default values
AGrapnelEquipmentSuperAaron::AGrapnelEquipmentSuperAaron()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);

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

	cable->SetVisibility(false);
}

void AGrapnelEquipmentSuperAaron::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AAaronCharacter* Character = Cast<AAaronCharacter>(GetParentActor());
	if (Character->GetCharacterMovement()->IsFalling())
	{
		Swing(DeltaTime);
	}
	else
	{
		SetActorTickEnabled(false);
		AfterHook();
	}
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
			canHook = false;
			playTLForLaser = false;
			hookMeshComponent->SetVisibility(false);

			myBullet = GetWorld()->SpawnActor<AGrappleHead>(hookMeshComponent->GetComponentLocation(), GetActorRotation());
			myBullet->locationToGo = locationToGrip;

			cable->SetVisibility(true);
			cable->SetAttachEndTo(myBullet, NAME_None, NAME_None);
			if (IsSwing)
			{
				ForceDirection = FVector(locationToGrip.X - GetParentActor()->GetActorLocation().X, locationToGrip.Y - GetParentActor()->GetActorLocation().Y, 0.0f);
				SetActorTickEnabled(true);
			}
			else
			{
				DisableInput(GetWorld()->GetFirstPlayerController());
				Hook();
			}
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
			IsSwing = IHookInterface::Execute_IsSwingSpot(outHit.GetActor());
			ParticleSystem->SetColorParameter(FName("color"), FLinearColor::Green);
			locationToGrip = outHit.Location;
			cable->CableLength = FVector::Distance(GetActorLocation(), locationToGrip);
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

void AGrapnelEquipmentSuperAaron::Swing(float DeltaTime)
{
	AAaronCharacter* Character = Cast<AAaronCharacter>(GetParentActor());
	FVector VDirection = GetActorLocation() - locationToGrip;

	float DistToGrab = VDirection.Size();
	cable->CableLength = DistToGrab;

	float DegreeSwing = UKismetMathLibrary::RadiansToDegrees(UKismetMathLibrary::Acos(FVector::DotProduct(VDirection.GetSafeNormal() * -1.0f, ForceDirection.GetSafeNormal())));

	Character->GetCharacterMovement()->AddForce(FVector::DotProduct(VDirection, Character->GetVelocity()) * VDirection.GetSafeNormal() * RopeForce);
	Character->GetCharacterMovement()->AddForce(Character->FpsCamera->GetForwardVector() * SwingSpeed);

	if (DegreeSwing > Degree + 90.0f)
	{
		SetActorTickEnabled(false);
		AfterHook();
	}
}

void AGrapnelEquipmentSuperAaron::Hook()
{
	FLatentActionInfo LatentActionInfo = FLatentActionInfo(1, 1, TEXT("AfterHook"), this);
	ACharacter* Character = GetWorld()->GetFirstPlayerController()->GetCharacter();
	UKismetSystemLibrary::MoveComponentTo(Character->GetRootComponent(), locationToGrip, Character->GetActorRotation(), true, false, TimeInterpolation, false, EMoveComponentAction::Move, LatentActionInfo);
}

void AGrapnelEquipmentSuperAaron::AfterHook()
{
	cable->SetVisibility(false);
	if (IsValid(myBullet))
	{
		myBullet->Destroy();
		myBullet = nullptr;
		hookMeshComponent->SetVisibility(true);
		foundHookSpot = false;
		playTLForLaser = true;
		canHook = true;
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}