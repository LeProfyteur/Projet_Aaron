// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	Tags.Add(FName(TEXT("Item")));
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
	//Copy
	ItemStruct->Name = ItemStructure->Name;
	ItemStruct->IsConsomable = ItemStructure->IsConsomable;
	ItemStruct->IsStackable = ItemStructure->IsStackable;
	ItemStruct->Category = ItemStructure->Category;
	ItemStruct->Class = ItemStructure->Class;
	ItemStruct->Description = ItemStructure->Description;
	ItemStruct->MaxStackSize = ItemStructure->MaxStackSize;
	ItemStruct->Thumbnail = ItemStructure->Thumbnail;

	Destroy();

	UE_LOG(LogActor, Warning, TEXT("Return itemStructure from AItem : %s"),*ItemStruct->Name);
}

