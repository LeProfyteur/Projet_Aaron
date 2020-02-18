// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	UPROPERTY()
		UStaticMeshComponent* StaticMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Activate();
		virtual void Activate_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnEquip();
		virtual void OnEquip_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnUnequip();
		virtual void OnUnequip_Implementation() override;
};
