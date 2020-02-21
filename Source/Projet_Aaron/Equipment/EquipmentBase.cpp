// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentBase.h"

// Sets default values
AEquipmentBase::AEquipmentBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Static mesh for visual representation of the equipment
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = StaticMeshComponent;
}

// Called when the game starts or when spawned
void AEquipmentBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEquipmentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEquipmentBase::Activate_Implementation(bool isPressed)
{
	UE_LOG(LogTemp, Warning, TEXT("Activated equipment"));
}

void AEquipmentBase::OnEquip_Implementation()
{
	
}

void AEquipmentBase::OnUnequip_Implementation()
{
	
}
