// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectInteractionInterface.h"
#include "Item.generated.h"

enum ESyringeType;

UCLASS()
class PROJET_AARON_API AItem : public AActor, public IObjectInteractionInterface
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
		void Interact(bool IsPressed, AActor* RefToInteractActor);
		virtual void Interact_Implementation(bool IsPressed, AActor* RefToInteractActor) override;

	UFUNCTION(BlueprintNativeEvent)
		FString GetLabel();
		virtual FString GetLabel_Implementation() override;

};
