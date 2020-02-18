// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Camera/CameraComponent.h"
#include  "Components/PostProcessComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Engine.h"
#include "StateManager.h"

#include "GameFramework/Character.h"
#include "CoreMinimal.h"
#include "FPS_Character.generated.h"

UCLASS()
class PROJET_AARON_API AFPS_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPS_Character();

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly)
	class UCameraComponent* fpsCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStateManager* stateManager;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPostProcessComponent* postProcess;
	
	UPROPERTY()
	class AActor *lastActorHit = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isNearClimbing = false;

	FHitResult *hitGrab;
	FHitResult *hitActor = nullptr;

	bool isSprinting = false;
	bool bPressedAlt = false;
	bool isNightVison = false;
	bool canGrab = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	
	void StartJump();
	void StopJump();
	
	void Sprint();
	void StopSprint();

	void StartAlt();
	void StopAlt();

	void Crouching();
	void Dodge(FVector direction);
	void Climb(float value);

	void RecoveryStamina(float deltaTime);
	void NightVision();

	void Action();
	void StopAction();
	void Analyse();

	void Grab();

	UFUNCTION(BlueprintCallable) void StopClimbing();

};
