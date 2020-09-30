// Fill out your copyright notice in the Description page of Project Settings.


#include "AaronCharacter.h"

AAaronCharacter::AAaronCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FpsCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_Camera"));
	FpsCamera->SetupAttachment(RootComponent);
	FpsCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FpsCamera->bUsePawnControlRotation = true;

	StatManager = CreateDefaultSubobject<UCharacterStatManager>(TEXT("StatManager"));
	PostProcessing = CreateDefaultSubobject<UPostProcessComponent>(TEXT("Post Processing"));

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->JumpZVelocity = StatManager->GetJumpForce();
	GetCharacterMovement()->AirControl = StatManager->GetAirControl();
	GetCharacterMovement()->GravityScale = StatManager->GetGravityScale();
	
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

void AAaronCharacter::MoveForward(float Value)
{
	GetCharacterMovement()->AddInputVector(GetActorForwardVector() * Value);
}

void AAaronCharacter::MoveRight(float Value)
{
	GetCharacterMovement()->AddInputVector(GetActorRightVector() * Value);
}
