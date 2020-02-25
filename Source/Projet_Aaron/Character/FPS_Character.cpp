// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_Character.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Engine.h"
#include "MyHUD.h"

// Sets default values
AFPS_Character::AFPS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FpsCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_Camera"));
	FpsCamera->SetupAttachment(RootComponent);
	FpsCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FpsCamera->bUsePawnControlRotation = true;
	
	StatManager = CreateDefaultSubobject<UCharacterStatManager>(TEXT("StateManager"));
	
	GetCharacterMovement()->MaxWalkSpeed = StatManager->GetActualSpeed();
	GetCharacterMovement()->JumpZVelocity = StatManager->GetJumpForce();
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	RightArmEquipment = CreateDefaultSubobject<UChildActorComponent>(TEXT("Right Arm Equipment"));
	RightArmEquipment->SetupAttachment(FpsCamera);

	LeftArmEquipment = CreateDefaultSubobject<UChildActorComponent>(TEXT("Left Arm Equipment"));
	LeftArmEquipment->SetupAttachment(FpsCamera);

	HeadEquipment = CreateDefaultSubobject<UChildActorComponent>(TEXT("Head Equipment"));
	HeadEquipment->SetupAttachment(FpsCamera);
}

// Called when the game starts or when spawned
void AFPS_Character::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFPS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CharacterMove();

	StatManager->RecoveryStamina(DeltaTime);

	FHitResult OutHit;
	FVector Start = FpsCamera->GetComponentLocation();
	FVector End = Start + FpsCamera->GetForwardVector() * 1000.0f;
	FCollisionQueryParams collisionParams;
	
	if(GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, collisionParams))
	{
		UStaticMeshComponent* actorMeshComponent = OutHit.Actor->FindComponentByClass<UStaticMeshComponent>();
		if (OutHit.Actor->ActorHasTag(FName(TEXT("Analysable"))))
		{
			actorMeshComponent->SetCustomDepthStencilValue(2);
			if (!HitActor || OutHit.Actor != HitActor->Actor)
				HitActor = new FHitResult(OutHit);
		}
		else if(OutHit.Actor->ActorHasTag(FName(TEXT("Destructable"))))
		{
			actorMeshComponent->SetCustomDepthStencilValue(3);
			if (!HitActor || OutHit.Actor != HitActor->Actor)
				HitActor = new FHitResult(OutHit);
		}
		else
		{
			if (HitActor)
			{
				actorMeshComponent = HitActor->Actor->FindComponentByClass<UStaticMeshComponent>();
				actorMeshComponent->SetCustomDepthStencilValue(1);
				HitActor = nullptr;
			}
		}
	} else if(HitActor)
	{
		UStaticMeshComponent* actorMeshComponent = HitActor->Actor->FindComponentByClass<UStaticMeshComponent>();
		actorMeshComponent->SetCustomDepthStencilValue(1);
		HitActor = nullptr;
	}
}

// Called to bind functionality to input
void AFPS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPS_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPS_Character::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AFPS_Character::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPS_Character::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPS_Character::StartJump);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFPS_Character::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFPS_Character::StopSprint);

	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AFPS_Character::StartAlt);
	PlayerInputComponent->BindAction("Dodge", IE_Released, this, &AFPS_Character::StopAlt);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFPS_Character::Crouching);
	
	PlayerInputComponent->BindAction("FireLeft", IE_Pressed,this, &AFPS_Character::ActivatePressedLeft);
	PlayerInputComponent->BindAction("FireLeft", IE_Released,this, &AFPS_Character::ActivateReleasedLeft);

	PlayerInputComponent->BindAction("FireRight", IE_Pressed, this, &AFPS_Character::ActivatePressedRight);
	PlayerInputComponent->BindAction("FireRight", IE_Released, this, &AFPS_Character::ActivateReleasedRight);
	
	PlayerInputComponent->BindAction("HeadAction", IE_Pressed, this, &AFPS_Character::ActivateHeadEquipment);
	
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AFPS_Character::Action);
	PlayerInputComponent->BindAction("Action", IE_Repeat, this, &AFPS_Character::Analyse);
	PlayerInputComponent->BindAction("Action", IE_Released,this, &AFPS_Character::StopAction);
}

void AFPS_Character::CharacterMove()
{
	FVector Direction = GetActorForwardVector() * ForwardAxisMovement + GetActorRightVector() * RightAxisMovement;
	if (bPressedAlt)
	{
		Dodge(Direction);
	}
	else if (IsNearClimbing)
	{
		//Climb(value);
	}
	else
	{
		AddMovementInput(GetActorForwardVector(), ForwardAxisMovement);
		AddMovementInput(GetActorRightVector(), RightAxisMovement);
	}

	if (IsSprinting && !StatManager->ConsumeStamina(StatManager->GetSprintStaminaCost()))
	{
		StopSprint();
	}
}


void AFPS_Character::MoveForward(float value)
{
	ForwardAxisMovement = value;
}

void AFPS_Character::MoveRight(float value)
{
	RightAxisMovement = value;
}

void AFPS_Character::StartJump()
{
	if(!GetCharacterMovement()->IsFalling() && StatManager->ConsumeStamina(StatManager->GetJumpStaminaCost()))
	{
		Jump();
	}
}

void AFPS_Character::Sprint()
{
	StatManager->SetActualSpeed(StatManager->GetSprintSpeed());
	IsSprinting = true;
}

void AFPS_Character::StopSprint()
{
	StatManager->ResetSpeed();
	IsSprinting = false;
}

void AFPS_Character::Dodge(FVector direction)
{
	if(!GetCharacterMovement()->IsFalling() && StatManager->ConsumeStamina(StatManager->GetDodgeStaminaCost()))
	{
		LaunchCharacter(direction * StatManager->GetDodgeForce(), true, false);
		bPressedAlt = false;
	}
}

void AFPS_Character::StartAlt()
{
	bPressedAlt = true;
}

void AFPS_Character::StopAlt()
{
	bPressedAlt = false;
}

void AFPS_Character::Crouching()
{  
	if (CanCrouch())
		Crouch();
	else
		UnCrouch();
}

void AFPS_Character::Action()
{
	if(HitActor)
	{
		 if (HitActor->Actor->ActorHasTag(FName(TEXT("Destructable"))))
		 {
			HitActor->Actor->Destroy();
			HitActor = nullptr;
		 }
	}
}

void AFPS_Character::StopAction()
{
	Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->ResetCircleRadius();
}


void AFPS_Character::Analyse()
{
	AMyHUD* myHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	float val = 0;
	myHUD->BarMatInstance->GetScalarParameterValue(FName(TEXT("Decimal")), val);
	myHUD->UpdateCircleRadius(val + 0.01f);
}

void AFPS_Character::Climb(float value)
{
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	AddMovementInput(GetActorUpVector(), value);
}

void AFPS_Character::StopClimbing()
{
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void AFPS_Character::ActivatePressedLeft()
{
	AActor* ChildActor = LeftArmEquipment->GetChildActor();
	if (IsValid(ChildActor) && ChildActor->Implements<UEquipmentInterface>())
		IEquipmentInterface::Execute_Activate(ChildActor, true);
}

void AFPS_Character::ActivateReleasedLeft()
{
	AActor* ChildActor = LeftArmEquipment->GetChildActor();
	if (IsValid(ChildActor) && ChildActor->Implements<UEquipmentInterface>())
		IEquipmentInterface::Execute_Activate(ChildActor, false);
}

void AFPS_Character::ActivatePressedRight()
{
	AActor* ChildActor = RightArmEquipment->GetChildActor();
	if (IsValid(ChildActor) && ChildActor->Implements<UEquipmentInterface>())
		IEquipmentInterface::Execute_Activate(ChildActor, true);
}

void AFPS_Character::ActivateReleasedRight()
{
	AActor* ChildActor = RightArmEquipment->GetChildActor();
	if (IsValid(ChildActor) && ChildActor->Implements<UEquipmentInterface>())
		IEquipmentInterface::Execute_Activate(ChildActor, false);
}

void AFPS_Character::ActivateHeadEquipment()
{
	AActor* ChildActor = HeadEquipment->GetChildActor();
	if (IsValid(ChildActor) && ChildActor->Implements<UEquipmentInterface>())
		IEquipmentInterface::Execute_Activate(ChildActor, true);
}















