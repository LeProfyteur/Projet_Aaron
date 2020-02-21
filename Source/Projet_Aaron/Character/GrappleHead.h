// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Projet_Aaron/Equipment/GrapnelEquipment.h"
#include "GrappleHead.generated.h"

UCLASS()
class PROJET_AARON_API AGrappleHead : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrappleHead();

	UPROPERTY(VisibleAnywhere)
		 UStaticMeshComponent* staticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UBoxComponent *boxCollision;

	UPROPERTY(VisibleAnywhere)
		FVector locationToGo;

	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* projectileMovement;

	class AGrapnelEquipment* equipment;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
