// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "Projet_Aaron/Equipment/HookInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HookSpot.generated.h"

UCLASS()
class PROJET_AARON_API AHookSpot : public AActor, public IHookInterface
{
	GENERATED_BODY()
	
public:	
	
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsSwing = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Sets default values for this actor's properties
	AHookSpot();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool IsSwingSpot_Implementation() override;

};
