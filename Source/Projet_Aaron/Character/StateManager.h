// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJET_AARON_API UStateManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStateManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite) float speed = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float sprintSpeedScalar = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float maxStamina = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float sprintCostStamina = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float recorveryStamina = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float maxLife = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float maxTechLife = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float jumpForce = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float bioLife;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float techLife;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float stamina;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION() void Heal(float bioHeal, float mecaHeal);
	UFUNCTION() void TakeDamage(float bioDamage, float mecaDamage);
	UFUNCTION() void Die();
		
};
