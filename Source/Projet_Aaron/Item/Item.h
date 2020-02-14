// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projet_Aaron/Interact_Interface.h"
#include "Item.generated.h"

UCLASS()
class PROJET_AARON_API AItem : public AActor, public IInteract_Interface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDA_ItemStructure* ItemStructure;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * \brief Use current item
	 * \return Return true if a item was used, false otherwise
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		bool UseItem();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		UDA_ItemStructure* Interact_Implementation() override;

	UFUNCTION(BlueprintNativeEvent)
		UDA_ItemStructure* InteractSafe_Implementation() override;

};
