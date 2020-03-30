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
		int NumberOfSlots=6;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<UDA_SlotStructure*> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<UDA_SlotStructure*> InventoryFlacon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<UDA_SlotStructure*> InventoryConsomable;

	UFUNCTION(BlueprintCallable)
		void AddToInventory(UDA_ItemStructure* ItemToAdd);

	UFUNCTION(BlueprintCallable)
		void RemoveFromInventory(UDA_SlotStructure* SlotToRemove);

	UFUNCTION(BlueprintCallable)
		void PrepareInventory();

	int GetIndexSlot(UDA_ItemStructure* ItemToSearch);
	int GetIndexSlotConso(UDA_ItemStructure* ItemToSearch);
	int GetIndexSlotSeringue(UDA_ItemStructure* ItemToSearch);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
