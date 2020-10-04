// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include <GameFramework/Character.h>
#include <Camera/CameraComponent.h>
#include "Projet_Aaron/StatManager/CharacterStatManager.h"
#include "Projet_Aaron/Character/AaronCharacterMovementComponent.h"
#include "AaronCharacter.generated.h"

UCLASS()
class PROJET_AARON_API AAaronCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAaronCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* FpsCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UPostProcessComponent* PostProcessing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* LeftArmEquipment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* RightArmEquipment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* HeadEquipment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* ChestEquipment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* LegsEquipment;

public:
	UFUNCTION(BlueprintCallable)
		void MoveForward(float Value);
	UFUNCTION(BlueprintCallable)
		void MoveRight(float Value);
	UFUNCTION(BlueprintCallable)
		void Turn(float Value);
	UFUNCTION(BlueprintCallable)
		void LookUp(float Value);
	
	UFUNCTION(BlueprintCallable)
		void StartClimbingWithLeftHand(const FVector& WorldPosition);
	UFUNCTION(BlueprintCallable)
		void StopClimbingWithLeftHand();
	
	UFUNCTION(BlueprintCallable)
		void StartClimbingWithRightHand(const FVector& WorldPosition);
	UFUNCTION(BlueprintCallable)
		void StopClimbingWithRightHand();

private:
	void TransitionToMovementState(EMovementState NewMovementState);
	void OnEnterMovementState(EMovementState MovementState);
	void OnExitMovementState(EMovementState MovementState);
	void DebugMovementState();

	void GroundedMovement(const FVector& Direction, float Speed);
	void DashMovement(const FVector& Direction, float Speed);
	void AirMovement(const FVector& Direction, float Speed);
	void ClimbMovement();
	void SlideMovement();

	void GroundedTransitions();
	void DashTransitions();
	void SlideTransitions();
	void AirTransitions();
	void SwimTransitions();
	void ClimbTransitions();

	void UpdateShouldClimb();

	//Dash Internal Variables
	float DashTimeAccumulator = 0.0f;
	FVector DashVector;

	//Slide Internal Variables
	float SlideMomentum;
	FVector LastActorLocation;

	//Climb Internal Variables
	bool UsingLeftGripPoint;
	FVector LeftGripPoint;
	bool UsingRightGripPoint;
	FVector RightGripPoint;
protected:
	UPROPERTY(BlueprintReadWrite, Category = "Acquisition")
		FVector InputVector = FVector::ZeroVector;
	FVector LastInputDirection = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, Category = "Acquisition")
		bool ShouldCrouch = false;
	UPROPERTY(BlueprintReadWrite, Category = "Acquisition")
		bool ShouldCrawl = false;
	UPROPERTY(BlueprintReadWrite, Category = "Acquisition")
		bool ShouldRun = false;
	UPROPERTY(BlueprintReadWrite, Category = "Acquisition")
		bool ShouldDash = false;
	UPROPERTY(BlueprintReadWrite, Category = "Acquisition")
		bool ShouldClimb = false;

	//Movement State
	UPROPERTY(BlueprintReadOnly)
		EMovementState CurrentMovementState = EMovementState::Run;
	
	//Metrics
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metrics")
		float CrouchSpeed = 400;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metrics")
		float WalkSpeed = 600;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metrics")
		float RunSpeed = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metrics")
		float DashSpeed = 3000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metrics")
		float DashDuration = 0.20f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metrics")
		float DashCooldown = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metrics")
		float SlideInitialRequiredSpeed = 800;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metrics")
		float SlideSpeed = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metrics")
		float SlideMinSlopeAngle = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metrics")
		float JumpForce = 464;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metrics")
		float SwimSpeed = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metrics")
		float CrawlSpeed = 700;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metrics")
		float InAirSpeed = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metrics")
		float GlidingSpeed = 700;
};