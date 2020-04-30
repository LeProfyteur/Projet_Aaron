// Fill out your copyright notice in the Description page of Project Settings.


#include "GrappleHead.h"

// Sets default values
AGrappleHead::AGrappleHead()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = boxCollision;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	staticMesh->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> hookMesh(TEXT("/Game/Projet_Aaron/CC/Equipment/Grapnel/Hook.Hook"));
	if(hookMesh.Succeeded())
		staticMesh->SetStaticMesh(hookMesh.Object);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	projectileMovement->InitialSpeed = 10000.0f;
	projectileMovement->MaxSpeed = 10000.0f;
	
}

// Called when the game starts or when spawned
void AGrappleHead::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGrappleHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(FVector::PointsAreNear(GetActorLocation(), locationToGo, 150.0f))
	{
		projectileMovement->SetVelocityInLocalSpace(FVector::ZeroVector);
		SetActorEnableCollision(false);
	}
}

