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
	return ItemStructure->IsConsomable;
}

FString AItem::GetLabel_Implementation()
{
	return (ItemStructure->Name + " [E]");
}

void AItem::Interact_Implementation(bool IsPressed, AActor* RefToInteractActor)
{
	//Copy
	if(IsPressed)
	{
		UInventaireComponent* inventaire = RefToInteractActor->FindComponentByClass<UInventaireComponent>();

		if(inventaire)
		{
			inventaire->AddToInventory(ItemStructure);
		}

		Destroy();
	}
}

