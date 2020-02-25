// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AItem::UseItem_Implementation()
{
	UE_LOG(LogActor, Error, TEXT("UseItem : Item.CPP"));
	return ItemStructure->IsConsomable;
}

FString AItem::GetLabel_Implementation()
{
	return ItemStructure->Name;
}

void AItem::Interact_Implementation(bool IsPressed, UDA_ItemStructure* ItemStruct)
{
	ItemStruct = ItemStructure;
	Destroy();
}

