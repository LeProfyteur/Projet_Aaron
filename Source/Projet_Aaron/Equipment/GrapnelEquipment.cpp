// Fill out your copyright notice in the Description page of Project Settings.


#include "GrapnelEquipment.h"
#include "Projet_Aaron/Character/FPS_Character.h"

AGrapnelEquipment::AGrapnelEquipment()
{
	PrimaryActorTick.bCanEverTick = true;

	SetActorEnableCollision(false);

	timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine"));
	updateFunction.BindUFunction(this, FName("TimelineCallback"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> hookArmMesh(TEXT("/Game/Projet_Aaron/CC/FirstPersonBP/Blueprints/Grappnel/Grapple_Hook2.Grapple_Hook2"));
	if (hookArmMesh.Succeeded())
		StaticMeshComponent->SetStaticMesh(hookArmMesh.Object);

	laser = CreateDefaultSubobject<UCableComponent>(TEXT("Laser"));
	laser->SetupAttachment(RootComponent);
	laser->NumSegments = 1;
	
	pointer = CreateDefaultSubobject<UChildActorComponent>(TEXT("Pointer"));
	pointer->SetChildActorClass(AGrapplePointer::StaticClass());
	pointer->SetupAttachment(laser);

	cable = CreateDefaultSubobject<UCableComponent>(TEXT("Cable"));
	cable->SetupAttachment(RootComponent);

	hookMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hook Mesh"));
	hookMeshComponent->SetupAttachment(cable);
	hookMeshComponent->SetRelativeLocation(FVector(60.0f, 0.0f, 7.0f), NULL);
	ConstructorHelpers::FObjectFinder<UStaticMesh> hookMesh(TEXT("/Game/Projet_Aaron/CC/FirstPersonBP/Blueprints/Grappnel/Hook.Hook"));
	if (hookMesh.Succeeded())
		hookMeshComponent->SetStaticMesh(hookMesh.Object);
}

void AGrapnelEquipment::BeginPlay()
{
	Super::BeginPlay();

	timeline->SetTimelineLength(5.0f);
	timeline->SetTimelinePostUpdateFunc(updateFunction);
	timeline->SetLooping(true);

	SetActorTickEnabled(false);

	cable->SetHiddenInGame(true, false);
}

void AGrapnelEquipment::Activate_Implementation(bool isPressed)
{
	if (isPressed)
	{
		if (!IsValid(myBullet) && canHook)
		{
			foundHookSpot = false;
			laser->SetHiddenInGame(false, true);
			PlayTimeline();
		}
	} else
	{
		if(foundHookSpot && canHook)
		{
			DisableInput(GetWorld()->GetFirstPlayerController());
			canHook = false;
			playTLForLaser = false;
			laser->SetHiddenInGame(true, true);
			cable->SetHiddenInGame(false, false);
			hookMeshComponent->SetHiddenInGame(true);
			myBullet = GetWorld()->SpawnActor<AGrappleHead>(hookMeshComponent->GetComponentLocation(), GetActorRotation());
			myBullet->equipment = this;
			myBullet->locationToGo = locationToGrip;
			cable->SetAttachEndTo(myBullet, FName(), FName());
		}
		else
		{
			laser->SetHiddenInGame(true, true);
		}
	}
}

void AGrapnelEquipment::OnEquip_Implementation()
{
	
}

void AGrapnelEquipment::OnUnequip_Implementation()
{
	
}

void AGrapnelEquipment::TimelineCallback()
{
	FHitResult outHit;
	FVector vStart;
	FVector vEnd;
	FCollisionQueryParams collisionParams(FName(TEXT("Laser")), false, this);
	
	if(playTLForLaser)
	{
		vStart = StaticMeshComponent->GetComponentLocation();
		AFPS_Character *c = Cast<AFPS_Character>(GetParentActor());
		vEnd = vStart + c->fpsCamera->GetForwardVector() * Distance;
		
		bool haveHit = GetWorld()->LineTraceSingleByChannel(outHit, vStart, vEnd, ECC_Visibility, collisionParams);
		if (haveHit && outHit.Actor->GetClass()->ImplementsInterface(UHookInterface::StaticClass()))
		{
			TArray<FVector> listOfHookSpot = IHookInterface::Execute_GiveMeHookSpot(outHit.GetActor());
			for(FVector v : listOfHookSpot)
			{
				vEnd = outHit.Actor->GetActorLocation() + v;
				collisionParams = FCollisionQueryParams(FName(TEXT("Laser")), false, outHit.GetActor());
				collisionParams.AddIgnoredActor(this);
				FHitResult test;
				if (!GetWorld()->LineTraceSingleByChannel(test, vStart, vEnd, ECC_Visibility, collisionParams))
				{
					locationToGrip = outHit.Location + v;
					foundHookSpot = true;
					UMaterialInstance*mat = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), NULL, TEXT("/Game/Projet_Aaron/CC/FirstPersonBP/Blueprints/Grappnel/Hook_Green.Hook_Green")));
					laser->SetMaterial(0, mat);
					updatePointerLocation();
					break;
				}
			}
		}
		else
		{
			UMaterialInstance* mat = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), NULL, TEXT("/Game/Projet_Aaron/CC/FirstPersonBP/Blueprints/Grappnel/Hook_Red.Hook_Red")));
			laser->SetMaterial(0, mat);
			
			if (haveHit)
				locationToGrip = outHit.Location;
			else
				locationToGrip = outHit.TraceEnd;
			
			foundHookSpot = false;
			updatePointerLocation();
		}
	}
}

void AGrapnelEquipment::updatePointerLocation()
{
	pointer->SetWorldLocation(locationToGrip);
	laser->SetAttachEndTo(pointer->GetChildActor(), FName(), FName());
}

void AGrapnelEquipment::PlayTimeline()
{
	if (timeline)
	{
		timeline->Play();
	}
}

void AGrapnelEquipment::Tick(float DeltaTime)
{
	AFPS_Character* c = Cast<AFPS_Character>(GetParentActor());
	if(FVector::PointsAreNear(locationToGrip, c->GetActorLocation(), 150.0f))
	{
		SetActorTickEnabled(false);
		timeline->Stop();
		cable->CableLength = 0.0f;
		cable->SetAttachEndTo(this, FName(), FName());
		cable->SetHiddenInGame(true, false);
		GetWorld()->DestroyActor(myBullet);
		hookMeshComponent->SetHiddenInGame(false, false);
		foundHookSpot = false;
		playTLForLaser = true;
		canHook = true;
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
	else
	{
		FVector launchVelocity = (locationToGrip - c->GetActorLocation()) * DeltaTime * 250.0f;
		c->LaunchCharacter(launchVelocity, true, true);
		laser->CableLength = FVector::Distance(GetActorLocation(), locationToGrip);
	}
}











