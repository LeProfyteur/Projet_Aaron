// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentBase.h"

// Sets default values
AEquipmentBase::AEquipmentBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Static mesh for visual representation of the equipment
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetGenerateOverlapEvents(false);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = StaticMeshComponent;
}

// Called when the game starts or when spawned
void AEquipmentBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEquipmentBase::Activate_Implementation(bool isPressed)
{
	//UE_LOG(LogTemp, Warning, TEXT("Activated equipment"));
}

void AEquipmentBase::OnEquip_Implementation(FCharacterSkills &Skills)
{
	//UE_LOG(LogTemp, Warning, TEXT("Equip equipment"));
}

void AEquipmentBase::OnUnequip_Implementation(FCharacterSkills &Skills)
{
	//UE_LOG(LogTemp, Warning, TEXT("Unequip equipment"));
}
