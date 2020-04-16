// Fill out your copyright notice in the Description page of Project Settings.


#include "GrapnelEquipmentSuperAaron.h"
#include "Projet_Aaron/Character/AaronCharacter.h"

// Sets default values
AGrapnelEquipmentSuperAaron::AGrapnelEquipmentSuperAaron()
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

void AGrapnelEquipmentSuperAaron::BeginPlay()
{
	Super::BeginPlay();

	timeline->SetTimelineLength(5.0f);
	timeline->SetTimelinePostUpdateFunc(updateFunction);
	timeline->SetLooping(true);

	SetActorTickEnabled(false);

	cable->SetHiddenInGame(true, false);
}

void AGrapnelEquipmentSuperAaron::Activate_Implementation(bool isPressed)
{
	if (isPressed)
	{
		if (!IsValid(myBullet) && canHook)
		{
			foundHookSpot = false;
			laser->SetHiddenInGame(false, true);
			PlayTimeline();
		}
	}
	else
	{
		if (foundHookSpot && canHook)
		{
			DisableInput(GetWorld()->GetFirstPlayerController());
			canHook = false;
			playTLForLaser = false;
			laser->SetHiddenInGame(true, true);
			cable->SetHiddenInGame(false, false);
			hookMeshComponent->SetHiddenInGame(true);
			myBullet = GetWorld()->SpawnActor<AGrappleHead>(AGrappleHead::StaticClass(), hookMeshComponent->GetComponentLocation(), GetActorRotation());
			myBullet->locationToGo = locationToGrip;
			cable->SetAttachEndTo(myBullet, NAME_None, NAME_None);
			Hook();
		}
		else
		{
			laser->SetHiddenInGame(true, true);
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
		AAaronCharacter* c = Cast<AAaronCharacter>(GetParentActor());
		vEnd = vStart + c->FpsCamera->GetForwardVector() * Distance;

		bool haveHit = GetWorld()->LineTraceSingleByChannel(outHit, vStart, vEnd, ECC_Visibility, collisionParams);
		if (haveHit && outHit.Actor->GetClass()->ImplementsInterface(UHookInterface::StaticClass()))
		{
			locationToGrip = outHit.Location;
			TimeInterpolation = (outHit.Distance * 0.25f) / 100.0f;
			foundHookSpot = true;
			UMaterialInstance* mat = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), NULL, TEXT("/Game/Projet_Aaron/CC/FirstPersonBP/Blueprints/Grappnel/Hook_Green.Hook_Green")));
			laser->SetMaterial(0, mat);
			updatePointerLocation();
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

void AGrapnelEquipmentSuperAaron::updatePointerLocation()
{
	pointer->SetWorldLocation(locationToGrip);
	laser->SetAttachEndTo(pointer->GetChildActor(), FName(), FName());
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
	cable->SetAttachEndTo(myBullet, NAME_None, FName("CableAttach"));
	FLatentActionInfo LatentActionInfo = FLatentActionInfo(1, 1, TEXT("AfterHook"), this);
	ACharacter* Character = GetWorld()->GetFirstPlayerController()->GetCharacter();
	UKismetSystemLibrary::MoveComponentTo(Character->GetRootComponent(), locationToGrip, Character->GetActorRotation(), true, false, TimeInterpolation, false, EMoveComponentAction::Move, LatentActionInfo);
}

void AGrapnelEquipmentSuperAaron::AfterHook()
{
	cable->CableLength = 0.0f;
	//cable->SetAttachEndTo(myBullet, NAME_None, FName("CableAttach"));
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