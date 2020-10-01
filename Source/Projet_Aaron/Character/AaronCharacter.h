// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include <GameFramework/Character.h>
#include <Camera/CameraComponent.h>
#include "../StatManager/CharacterStatManager.h"
#include "AaronCharacter.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Crouch UMETA(DisplayName = "Crouch"),
	Walk UMETA(DisplayName = "Walk"),
	Run UMETA(DisplayName = "Run"),
	Dash UMETA(DisplayName = "Dash"),
	Slide UMETA(DisplayName = "Slide"),
	Swim UMETA(DisplayName = "Swim"),
	Crawl UMETA(DisplayName = "Crawl"),
	InAir UMETA(DisplayName = "InAir"),
	Glide UMETA(DisplayName = "Glide"),
	Climb UMETA(DisplayName = "Climb"),
};

UCLASS()
class PROJET_AARON_API AAaronCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAaronCharacter();
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
		void SetMovementState(EMovementState NewMovementMethod);
private:
	void OnEnterMovementState(EMovementState MovementState);
	void OnExitMovementState(EMovementState MovementState);

protected:
	//Inputs
	FVector InputVector = FVector::ZeroVector;

	//Movement State
	UPROPERTY(BlueprintReadOnly)
		EMovementState MovementMethod = EMovementState::Run;
	
	//Metrics
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrouchSpeed = 400;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WalkSpeed = 600;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RunSpeed = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DashSpeed = 2000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float JumpForce = 464;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SwimSpeed = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrawlSpeed = 700;

	//TODO Dodge, Climb, Slide, Glide Metrics
};