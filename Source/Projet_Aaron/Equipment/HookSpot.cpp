// Fill out your copyright notice in the Description page of Project Settings.


#include "HookSpot.h"

// Sets default values
AHookSpot::AHookSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
		
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	RootComponent = SphereCollision;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);;

}

// Called when the game starts or when spawned
void AHookSpot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHookSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AHookSpot::IsSwingSpot_Implementation()
{
	return IsSwing;
}

