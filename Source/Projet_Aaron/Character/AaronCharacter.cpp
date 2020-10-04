// Fill out your copyright notice in the Description page of Project Settings.


#include "AaronCharacter.h"

#include "Math/UnitConversion.h"

//Chaining ifs is boring. That's just a one liner implementation for a transition selector
#define MAKE_TRANSITION(Condition, MovementState) if (!!(Condition)) { TransitionToMovementState(MovementState); return; }

AAaronCharacter::AAaronCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UAaronCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	FpsCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_Camera"));
	FpsCamera->SetupAttachment(RootComponent);
	FpsCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FpsCamera->bUsePawnControlRotation = true;


	PostProcessing = CreateDefaultSubobject<UPostProcessComponent>(TEXT("Post Processing"));
	
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
	switch (CurrentMovementState)
	{
	case EMovementState::Crouch:
		GroundedMovement(InputVector, CrouchSpeed);
		GroundedTransitions();
		break;
	case EMovementState::Walk:
		GroundedMovement(InputVector, WalkSpeed);
		GroundedTransitions();
		break;
	case EMovementState::Run:
		GroundedMovement(InputVector, RunSpeed);
		GroundedTransitions();
		break;

	case EMovementState::Dash:
		LaunchCharacter(DashVector * DashSpeed, true, false);
		DashTransitions();
		break;
		
	case EMovementState::Slide:
		SlideMovement();
		SlideTransitions();
		break;
		
	case EMovementState::Swim:
		GetMovementComponent()->AddInputVector(FpsCamera->GetForwardVector() * SwimSpeed);
		SwimTransitions();
		break;

	case EMovementState::Crawl:
		GetMovementComponent()->AddInputVector(FpsCamera->GetForwardVector() * CrawlSpeed);
		SwimTransitions();
		break;
		
	case EMovementState::Climb:
		ClimbMovement();
		ClimbTransitions();
		break;

	case EMovementState::InAir:
		AirMovement(InputVector, InAirSpeed);
		AirTransitions();
		break;

	case EMovementState::Glide:
		AirMovement(InputVector, GlidingSpeed);
		AirTransitions();
		break;
	}

	LastInputDirection = InputVector;
	InputVector = FVector::ZeroVector;
	DashTimeAccumulator += DeltaSeconds;
}

void AAaronCharacter::MoveForward(float Value)
{
	InputVector += GetActorForwardVector() * Value;
}

void AAaronCharacter::MoveRight(float Value)
{
	InputVector += GetActorRightVector() * Value;
}

void AAaronCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AAaronCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AAaronCharacter::StartClimbingWithLeftHand(const FVector& WorldPosition)
{
	UsingLeftGripPoint = true;
	LeftGripPoint = WorldPosition;
	UpdateShouldClimb();
}

void AAaronCharacter::StopClimbingWithLeftHand()
{
	UsingLeftGripPoint = false;
	UpdateShouldClimb();
}


void AAaronCharacter::StartClimbingWithRightHand(const FVector& WorldPosition)
{
	UsingRightGripPoint = true;
	RightGripPoint = WorldPosition;
	UpdateShouldClimb();
}

void AAaronCharacter::StopClimbingWithRightHand()
{
	UsingRightGripPoint = false;
	UpdateShouldClimb();
}

void AAaronCharacter::TransitionToMovementState(EMovementState NewMovementState)
{
	if (CurrentMovementState != NewMovementState)
	{
		//Let the Current MovementState Clean up after itself
		OnExitMovementState(CurrentMovementState);
		//Actual Update
		CurrentMovementState = NewMovementState;
		//Let the New Movement State Init
		OnEnterMovementState(CurrentMovementState);
		DebugMovementState();
	}
}

void AAaronCharacter::OnEnterMovementState(EMovementState MovementState)
{	
	switch (MovementState)
	{
	case EMovementState::Crouch:
		GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
		break;
	case EMovementState::Walk:
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		break;
	case EMovementState::Run:
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		break;
	case EMovementState::Dash:
		DashTimeAccumulator = 0;
		//Offset from the ground a tiny bit
		SetActorLocation(GetActorLocation() + FVector(0, 0, 1));
		//Prepare the Dash Vector (Horizontal in last input direction)
		DashVector = LastInputDirection;
		DashVector.Z = 0;
		DashVector.Normalize();
		break;
	case EMovementState::Slide:
		GetCharacterMovement()->MaxWalkSpeed = SlideSpeed;
		SlideMomentum = FMath::Min(SlideSpeed, GetVelocity().Size());
		LastActorLocation = GetActorLocation();
		break;
	case EMovementState::Climb:
		GetCharacterMovement()->SetMovementMode(MOVE_Custom);
		break;
	case EMovementState::Swim:
		break;
	case EMovementState::Crawl:
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
		break;
	case EMovementState::Walk:
		break;
	case EMovementState::Run:
		break;
	case EMovementState::Dash:
		DashTimeAccumulator = 0;
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->Launch(-GetVelocity());
		break;
	case EMovementState::Climb:
		GetCharacterMovement()->SetMovementMode(MOVE_Falling);
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

void AAaronCharacter::DebugMovementState()
{
	FString CurrentState = "Unknown";
	switch (CurrentMovementState)
	{
	case EMovementState::Crouch:	CurrentState = "Crouch"; break;
	case EMovementState::Walk:		CurrentState = "Walk";  break;
	case EMovementState::Run:		CurrentState = "Run"; break;
	case EMovementState::Dash:		CurrentState = "Dash"; break;
	case EMovementState::Slide:		CurrentState = "Slide"; break;
	case EMovementState::Swim:		CurrentState = "Swim"; break;
	case EMovementState::Crawl:		CurrentState = "Crawl"; break;
	case EMovementState::InAir:		CurrentState = "InAir"; break;
	case EMovementState::Glide:		CurrentState = "Glide"; break;
	case EMovementState::Climb:		CurrentState = "Climb"; break;
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, "MovementState : " + CurrentState);
}

void AAaronCharacter::GroundedMovement(const FVector& Direction, float Speed)
{
	GetMovementComponent()->AddInputVector(Direction.GetSafeNormal() * Speed);
}

void AAaronCharacter::DashMovement(const FVector& Direction, float Speed)
{
	GetMovementComponent()->AddInputVector(Direction.GetSafeNormal() * Speed);
}

void AAaronCharacter::AirMovement(const FVector& Direction, float Speed)
{
	FVector FlatDirection = Direction * Speed;
	FlatDirection.Z = 0;
	GetMovementComponent()->AddInputVector(FlatDirection);
}

void AAaronCharacter::ClimbMovement()
{
	FVector TargetGripPoint(FVector::ZeroVector);

	if (UsingLeftGripPoint || UsingRightGripPoint)
	{

		if (UsingLeftGripPoint)
		{
			TargetGripPoint += LeftGripPoint;
		}

		if (UsingRightGripPoint)
		{
			TargetGripPoint += RightGripPoint;
		}

		//Average the two GripPoints if both are being used
		if (UsingLeftGripPoint && UsingRightGripPoint)
		{
			TargetGripPoint /= 2;
		}

		FVector DesiredLocation = FMath::Lerp(GetActorLocation(), TargetGripPoint, 0.1f);
		SetActorLocation(DesiredLocation);
	}
}

void AAaronCharacter::SlideMovement()
{
	const FVector ActorVelocity = GetActorLocation() - LastActorLocation;
	LastActorLocation = GetActorLocation();

	if (ActorVelocity.IsNearlyZero()) // Likely Stopping/Blocked
	{
		SlideMomentum = 0;
	}

	const FVector Direction = ActorVelocity.GetSafeNormal();

	if (ActorVelocity.Z >= 0) // Sliding up-hill
	{
		const float MomentumLoss = FVector::DotProduct(Direction, GetActorForwardVector());
		SlideMomentum = SlideMomentum * (MomentumLoss * MomentumLoss);
	}

	GetCharacterMovement()->AddInputVector(Direction * SlideMomentum);
}


void AAaronCharacter::GroundedTransitions()
{
	const float Speed = GetVelocity().Size();
	//Hard Transitions (Different locomotion mode)
	MAKE_TRANSITION(ShouldDash && DashTimeAccumulator > DashCooldown,	EMovementState::Dash);
	MAKE_TRANSITION(GetMovementComponent()->IsFalling(),				EMovementState::InAir);
	MAKE_TRANSITION(GetMovementComponent()->IsInWater(),				EMovementState::Swim);
	MAKE_TRANSITION(ShouldCrouch && Speed > SlideInitialRequiredSpeed,	EMovementState::Slide);
	MAKE_TRANSITION(ShouldClimb,										EMovementState::Climb);
	//Soft Transitions (speed changes)
	MAKE_TRANSITION(ShouldRun,											EMovementState::Run);
	MAKE_TRANSITION(ShouldCrouch && Speed <= WalkSpeed,					EMovementState::Crouch);
	MAKE_TRANSITION(true,												EMovementState::Walk);
}

void AAaronCharacter::DashTransitions()
{
	//Grounded Transitions only after the Dash is finished
	if (DashTimeAccumulator > DashDuration)
	{
		GroundedTransitions();
	}
}

void AAaronCharacter::SlideTransitions()
{
	MAKE_TRANSITION(GetMovementComponent()->IsFalling(),				EMovementState::InAir);
	MAKE_TRANSITION(GetMovementComponent()->IsInWater(),				EMovementState::Swim);
	MAKE_TRANSITION(ShouldClimb,										EMovementState::Climb);
	MAKE_TRANSITION(ShouldDash && DashTimeAccumulator > DashCooldown,	EMovementState::Dash);
	MAKE_TRANSITION(SlideMomentum <= CrouchSpeed,						EMovementState::Crouch);
}

void AAaronCharacter::AirTransitions()
{
	MAKE_TRANSITION(GetMovementComponent()->IsInWater(),				EMovementState::Swim);
	MAKE_TRANSITION(GetMovementComponent()->IsMovingOnGround(),			EMovementState::Walk);
}

void AAaronCharacter::SwimTransitions()
{
	MAKE_TRANSITION(ShouldClimb,							EMovementState::Climb);
	MAKE_TRANSITION(!GetMovementComponent()->IsInWater(),	EMovementState::Walk);
}

void AAaronCharacter::ClimbTransitions()
{
	MAKE_TRANSITION(!ShouldClimb, EMovementState::InAir);
}

void AAaronCharacter::UpdateShouldClimb()
{
	ShouldClimb = UsingLeftGripPoint || UsingRightGripPoint;
}