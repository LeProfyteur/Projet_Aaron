// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DA_ItemStructure.h"
#include "DA_SlotStructure.h"
#include "Components/ActorComponent.h"
#include "InventaireComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJET_AARON_API UInventaireComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventaireComponent();
	/*TArray<AWeapon*> ListWeapon;
	TArray<AObjetRecup*> ListItems;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString InventoryName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int NumberOfSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UDA_SlotStructure*> Inventory;

	UFUNCTION(BlueprintCallable)
		void AddToInventory(UDA_ItemStructure* ItemToAdd);

	UFUNCTION(BlueprintCallable)
		void RemoveFromInventory(UDA_SlotStructure* SlotToRemove);

	UFUNCTION(BlueprintCallable)
		void PrepareInventory();

	int GetIndexSlot(UDA_ItemStructure* ItemToSearch);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
