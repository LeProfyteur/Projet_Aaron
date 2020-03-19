// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "Components/StaticMeshComponent.h"
#include "EquipmentInterface.h"
#include "EquipmentBase.generated.h"

UCLASS()
class PROJET_AARON_API AEquipmentBase : public AActor, public IEquipmentInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipmentBase();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Activate(bool isPressed);
		virtual void Activate_Implementation(bool isPressed) override; 

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnEquip();
		virtual void OnEquip_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnUnequip();
		virtual void OnUnequip_Implementation() override;
};
