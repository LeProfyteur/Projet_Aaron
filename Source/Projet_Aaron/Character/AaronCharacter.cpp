// Fill out your copyright notice in the Description page of Project Settings.


#include "AaronCharacter.h"

AAaronCharacter::AAaronCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FpsCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_Camera"));
	FpsCamera->SetupAttachment(RootComponent);
	FpsCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FpsCamera->bUsePawnControlRotation = true;

	PostProcessing = CreateDefaultSubobject<UPostProcessComponent>(TEXT("Post Processing"));

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	
	RightArmEquipment = CreateDefaultSubobject<UChildActorComponent>(TEXT("Right Arm Equipment"));
	RightArmEquipment->SetupAttachment(GetMesh(), FName("RightArm"));

	LeftArmEquipment = CreateDefaultSubobject<UChildActorComponent>(TEXT("Left Arm Equipment"));
	LeftArmEquipment->SetupAttachment(GetMesh(), FName("LeftArm"));
	
	HeadEquipment = CreateDefaultSubobject<UChildActorComponent>(TEXT("Head Equipment"));
	HeadEquipment->SetupAttachment(FpsCamera);

	ChestEquipment = CreateDefaultSubobject<UChildActorComponent>(TEXT("Chest Equipment"));
	ChestEquipment->SetupAttachment(FpsCamera);

	LegsEquipment = CreateDefaultSubobject<UChildActorComponent>(TEXT("Legs Equipment"));
	LegsEquipment->SetupAttachment(FpsCamera);
}

void AAaronCharacter::Tick(float DeltaSeconds)
{
	InputVector.Normalize();
	switch (MovementMethod)
	{
	case EMovementState::Crouch:
		GetMovementComponent()->AddInputVector(InputVector * CrouchSpeed);
		break;
	case EMovementState::Walk:
		GetMovementComponent()->AddInputVector(InputVector * WalkSpeed);
		break;
	case EMovementState::Run:
		GetMovementComponent()->AddInputVector(InputVector * RunSpeed);
		break;
	case EMovementState::Swim:
		GetMovementComponent()->AddInputVector(FpsCamera->GetForwardVector() * SwimSpeed);
		break;
	case EMovementState::Crawl:
		GetMovementComponent()->AddInputVector(FpsCamera->GetForwardVector() * CrawlSpeed);
		break;
	case EMovementState::Climb:
		break;
	case EMovementState::Slide:
		break;
	case EMovementState::InAir:
		break;
	case EMovementState::Glide:
		break;
	case EMovementState::Dash:
		break;
	}

	InputVector = FVector::ZeroVector;
}


void AAaronCharacter::MoveForward(float Value)
{
	GetMovementComponent()->AddInputVector(GetActorForwardVector() * Value);
}

void AAaronCharacter::MoveRight(float Value)
{
	GetMovementComponent()->AddInputVector(GetActorRightVector() * Value);
}

void AAaronCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AAaronCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AAaronCharacter::SetMovementState(EMovementState NewMovementMethod)
{
	if (MovementMethod != NewMovementMethod)
	{
		OnExitMovementState(MovementMethod);
		
		MovementMethod = NewMovementMethod;
		
		OnEnterMovementState(MovementMethod);
	}
}

void AAaronCharacter::OnEnterMovementState(EMovementState MovementState)
{
	switch (MovementState)
	{
	case EMovementState::Crouch:
		GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;
		GetCharacterMovement()->Crouch();
		break;
	case EMovementState::Walk:
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		break;
	case EMovementState::Run:
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		break;
	case EMovementState::Dash:
		GetCharacterMovement()->MaxWalkSpeed = DashSpeed;
		break;
	case EMovementState::Climb:
		GetCharacterMovement()->SetMovementMode(MOVE_Custom);
		break;
	case EMovementState::Swim:
		break;
	case EMovementState::Crawl:
		break;
	case EMovementState::Slide:
		break;
	case EMovementState::Glide:
		break;
	case EMovementState::InAir:
		break;
	}
}

void AAaronCharacter::OnExitMovementState(EMovementState MovementState)
{
	switch (MovementState)
	{
	case EMovementState::Crouch:
		GetCharacterMovement()->UnCrouch();
		break;
	case EMovementState::Walk:
		break;
	case EMovementState::Run:
		break;
	case EMovementState::Dash:
		break;
	case EMovementState::Climb:
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		break;
	case EMovementState::Slide:
		break;
	case EMovementState::Glide:
		break;
	case EMovementState::Swim:
		break;
	case EMovementState::Crawl:
		break;
	case EMovementState::InAir:
		break;
	default:;
	}
}