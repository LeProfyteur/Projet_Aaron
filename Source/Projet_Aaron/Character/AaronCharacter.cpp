// Fill out your copyright notice in the Description page of Project Settings.


#include "AaronCharacter.h"

#include "Projet_Aaron/Save/AaronGameUserSettings.h"

// Sets default values
AAaronCharacter::AAaronCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRComponent = CreateDefaultSubobject<USceneComponent>(TEXT("VR Component"));
	VRComponent->SetupAttachment(RootComponent);

	FpsCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_Camera"));
	FpsCamera->SetupAttachment(VRComponent);
	FpsCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FpsCamera->bUsePawnControlRotation = true;

	StatManager = CreateDefaultSubobject<UCharacterStatManager>(TEXT("StatManager"));
	PostProcessing = CreateDefaultSubobject<UPostProcessComponent>(TEXT("Post Processing"));

	CharacterMovement = GetCharacterMovement();
	CharacterMovement->JumpZVelocity = StatManager->GetJumpForce();
	CharacterMovement->GetNavAgentPropertiesRef().bCanCrouch = true;
	
	RightArmEquipment = CreateDefaultSubobject<UChildActorComponent>(TEXT("Right Arm Equipment"));
	RightArmEquipment->SetupAttachment(FpsCamera);

	LeftArmEquipment = CreateDefaultSubobject<UChildActorComponent>(TEXT("Left Arm Equipment"));
	LeftArmEquipment->SetupAttachment(FpsCamera);

	HeadEquipment = CreateDefaultSubobject<UChildActorComponent>(TEXT("Head Equipment"));
	HeadEquipment->SetupAttachment(FpsCamera);

	ChestEquipment = CreateDefaultSubobject<UChildActorComponent>(TEXT("Chest Equipment"));
	ChestEquipment->SetupAttachment(FpsCamera);

	InventaireComponent = CreateDefaultSubobject<UInventaireComponent>(TEXT("InventaireComponent"));
	InventaireComponent->PrepareInventory();

	VaultTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Vault Timeline"));

	UpdateTimeline.BindUFunction(this, FName("UpdateTimelineFunction"));
	FinishTimeLine.BindUFunction(this, FName("EndTimelineFunction"));

	
}

void AAaronCharacter::AddControllerYawInput(float Val)
{
	Super::AddControllerYawInput(Val * UserSettings->GetMouseSensivity());
}

void AAaronCharacter::AddControllerPitchInput(float Val)
{
	Super::AddControllerPitchInput(Val * UserSettings->GetMouseSensivity());
}

// Called when the game starts or when spawned
void AAaronCharacter::BeginPlay()
{
	Super::BeginPlay();
	MovementState = EMovementState::Run;
	VaultTimeline->AddInterpFloat(CurveFloat, UpdateTimeline);
	VaultTimeline->SetTimelineFinishedFunc(FinishTimeLine);
	CharacterMovement->AirControl = StatManager->GetAirControl();
	CharacterMovement->GravityScale = StatManager->GetGravityScale();

	UserSettings = Cast<UAaronGameUserSettings>(GEngine->GetGameUserSettings());

	LeftArmEquipmentClass = LeftArmEquipment->GetChildActorClass();
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAaronCharacter::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AAaronCharacter::OnEndOverlap);

	UpdateBindAction();
}

void AAaronCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APhysicsVolume* WaterVolume = Cast<APhysicsVolume>(OtherActor);
	if(WaterVolume && WaterVolume->bWaterVolume)
	{
		//UE_LOG(LogActor, Error, TEXT("In Water"));
		IsInWater = true;
		FBoxSphereBounds WaterBounds = WaterVolume->GetBounds();
		WaterHeight = WaterBounds.Origin.Z + WaterBounds.BoxExtent.Z;
	}
}

void AAaronCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APhysicsVolume* WaterVolume = Cast<APhysicsVolume>(OtherActor);
	if (WaterVolume && WaterVolume->bWaterVolume)
		IsInWater = false;
}

// Called every frame
void AAaronCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (StatManager->Skills.SuperJump && bPressedJump && JumpMultPercent < 1.0f)
	{
		JumpMultPercent += 0.25f * DeltaTime;
		if (JumpMultPercent > 1.0f)
			JumpMultPercent = 1.0f;
	}

	if (IsInWater && GetMesh()->GetSocketLocation(FName("head")).Z < WaterHeight)
	{
		if (!StatManager->Skills.Gills)
			StatManager->ConsumeOxygene(1.0f * DeltaTime);
	}
	else
		StatManager->RecoveryOxygene(DeltaTime);

	if (MovementState == EMovementState::Sprint && CharacterMovement->Velocity.Size() > 0.0f)
	{
		if (!StatManager->ConsumeStamina(StatManager->GetSprintStaminaCost() * DeltaTime))
			MovementState = EMovementState::Run;
	} else if (MovementState == EMovementState::Sprint && CharacterMovement->Velocity.Size() <= 0.0f)
		MovementState = EMovementState::Run;
	else
		StatManager->RecoveryStamina(DeltaTime);

	if (MovementState == EMovementState::Slide)
	{
		FHitResult HitResult;
		FVector Start = GetActorLocation();
		FVector End = GetActorLocation() - GetActorUpVector() * 200.0f;
		GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

		if (HitResult.IsValidBlockingHit())
		{
			FVector GroundNormal = HitResult.ImpactNormal;
			float GroundAngle = FVector::DotProduct(GroundNormal, SlideRotation);
			if (GroundAngle >= StatManager->GetSlopeSlideAngle()) //We are on a slope steep enough
			{
				float SlideVelocity = StatManager->GetSprintSpeed();
				CharacterMovement->Velocity = FVector(SlideVelocity * SlideRotation.X, SlideVelocity * SlideRotation.Y, 0.0f);
			} else if (GroundAngle <= -(StatManager->GetSlopeStoppingAngle()))
			{
				CharacterMovement->Velocity = FVector::ZeroVector;
			}
		}
	}

	if (MovementState == EMovementState::Slide && (CharacterMovement->Velocity.Size() <= 0.0f || CharacterMovement->IsSwimming()))
	{
		CharacterMovement->GroundFriction = 8.0f;
		MovementState = EMovementState::Run;
	}
		
	if (MovementState == EMovementState::Climb)
		Climb(DeltaTime);
	else
		UpdateSpeed();

	//ItemWheel
	if (CurrentTimePressedItemWheel > 0.f)
	{
		CurrentTimePressedItemWheel += DeltaTime;
		if (!WheelDisplayed && CurrentTimePressedItemWheel >= UserSettings->GetHoldingTimeWheelSec())
		{
			DisplayWheel();
			WheelDisplayed = true;
		}
	}

	//Detecting pickable objects
	FHitResult OutHit;
	FVector Start = FpsCamera->GetComponentLocation();
	FVector End = Start + FpsCamera->GetForwardVector() * RaycastDistanceInventory;
	FCollisionQueryParams collisionParams;

	if (GetWorld()->SweepSingleByChannel(OutHit, Start, End, FpsCamera->GetComponentRotation().Quaternion(), ECC_Visibility, FCollisionShape::MakeCapsule(50, 50), collisionParams))
	{
		UStaticMeshComponent* actorMeshComponent = OutHit.Actor->FindComponentByClass<UStaticMeshComponent>();
		if (OutHit.GetActor()->Implements<UObjectInteractionInterface>())
		{
			if (!HitActor || OutHit.Actor != HitActor->Actor)
				HitActor = new FHitResult(OutHit);

			InventoryCastObject->nameTextItem = IObjectInteractionInterface::Execute_GetLabel(OutHit.GetActor());
		}
		else
		{
			InventoryCastObject->nameTextItem = "";
		}
	}
	else if (HitActor)
	{
		InventoryCastObject->nameTextItem = "";
		HitActor = nullptr;
	}

	if (CrouchJumped)
	{
		Jump();
		CrouchJumped = false;
	}
}

// Called to bind functionality to input
void AAaronCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AAaronCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAaronCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AAaronCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AAaronCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AAaronCharacter::StartJumping);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AAaronCharacter::EndJumping);

	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &AAaronCharacter::ToggleWalk);

	/*if (UserSettings->GetIsToggleSprint())
	{
		PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AAaronCharacter::ToggleSprint);
	} else
	{
		PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AAaronCharacter::StartSprinting);
		PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AAaronCharacter::StopSprinting);
	}*/

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AAaronCharacter::ToggleCrouch);

	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AAaronCharacter::Dodge);

	PlayerInputComponent->BindAction("SwitchGrapnelMod", IE_Pressed, this, &AAaronCharacter::EnableDisableGrapnel);
	
	PlayerInputComponent->BindAction("FireLeft", IE_Pressed, this, &AAaronCharacter::ActivatePressedLeft);
	PlayerInputComponent->BindAction("FireLeft", IE_Released, this, &AAaronCharacter::ActivateReleasedLeft);

	PlayerInputComponent->BindAction("FireRight", IE_Pressed, this, &AAaronCharacter::ActivatePressedRight);
	PlayerInputComponent->BindAction("FireRight", IE_Released, this, &AAaronCharacter::ActivateReleasedRight);

	PlayerInputComponent->BindAction("TorsoAction", IE_Pressed, this, &AAaronCharacter::ActivatePressedChest);

	PlayerInputComponent->BindAction("HeadAction", IE_Pressed, this, &AAaronCharacter::ActivateHeadEquipment);
	PlayerInputComponent->BindAction("NightVision", IE_Pressed, this, &AAaronCharacter::EnableDisableNightVision);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AAaronCharacter::Interact);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AAaronCharacter::StopInteract);

	PlayerInputComponent->BindAction("Scan", IE_Repeat, this, &AAaronCharacter::Scan);
	PlayerInputComponent->BindAction("Scan", IE_Pressed, this, &AAaronCharacter::Scan);
	PlayerInputComponent->BindAction("Scan", IE_Released, this, &AAaronCharacter::ScanRelease);
	
	PlayerInputComponent->BindAction("ItemWheel", IE_Pressed, this, &AAaronCharacter::PressedItemWheel);
	PlayerInputComponent->BindAction("ItemWheel", IE_Released, this, &AAaronCharacter::ReleaseItemWheel);

	for (int i = 0; i < PlayerInputComponent->GetNumActionBindings(); i++)
	{
		if (PlayerInputComponent->GetActionBinding(i).GetActionName().Compare(FName("FireLeft")) == 0)
			IndexFireLeftAction = i;
	}
}

void AAaronCharacter::EnableDisableNightVision()
{
	if (PostProcessing->Settings.WeightedBlendables.Array[0].Weight)
		PostProcessing->Settings.WeightedBlendables.Array[0].Weight = 0.0f;
	else
		PostProcessing->Settings.WeightedBlendables.Array[0].Weight = 1.0f;
}

void AAaronCharacter::EnableDisableGrapnel()
{
	if (GrapnelClass->IsValidLowLevel() && !IsGrapnelMod)
	{
		IsGrapnelMod = true;
		LeftArmEquipment->SetChildActorClass(GrapnelClass);
	} else if (IsGrapnelMod)
	{
		IsGrapnelMod = false;
		LeftArmEquipment->SetChildActorClass(LeftArmEquipmentClass);
	}
}

void AAaronCharacter::Climb(float DeltaTime)
{
	FVector LerpPosition = FMath::Lerp(GetActorLocation(), ClimbPosition, StatManager->GetClimbSpeed());
	SetActorLocation(LerpPosition);
}

void AAaronCharacter::UpdateSpeed()
{
	float Multiplier = StatManager->GetSpeedMultiplier();
	switch(MovementState)
	{
	case EMovementState::Run:
		CharacterMovement->MaxWalkSpeed = StatManager->GetRunSpeed() * Multiplier;
		CharacterMovement->MaxWalkSpeedCrouched = StatManager->GetCrouchRunSpeed() * Multiplier;
		CharacterMovement->MaxSwimSpeed = StatManager->GetSwimmingSpeed() * Multiplier;
		break;
	case EMovementState::Walk:
		CharacterMovement->MaxWalkSpeed = StatManager->GetWalkSpeed() * Multiplier;
		CharacterMovement->MaxWalkSpeedCrouched = StatManager->GetCrouchWalkSpeed() * Multiplier;
		CharacterMovement->MaxSwimSpeed = StatManager->GetSwimmingSpeed() * Multiplier;
		break;
	case EMovementState::Sprint:
		CharacterMovement->MaxWalkSpeed = StatManager->GetSprintSpeed() * Multiplier;
		CharacterMovement->MaxWalkSpeedCrouched = StatManager->GetSprintSpeed() * Multiplier;
		CharacterMovement->MaxSwimSpeed = StatManager->GetSwimmingSprintSpeed() * Multiplier;
		break;
	default: ;
	}
}

FVector AAaronCharacter::GetCharacterDirection() const
{
	FVector Direction = GetInputAxisValue("MoveForward") * GetActorForwardVector() + GetInputAxisValue("MoveRight") * GetActorRightVector();
	Direction.Normalize();
	return Direction;
}

void AAaronCharacter::MoveForward(float Value)
{
	FVector ForwardVector = FpsCamera->GetForwardVector();
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		ForwardVector = GetActorForwardVector();

	if (CharacterMovement->IsSwimming())
		AddMovementInput(ForwardVector, Value);
	else if (MovementState != EMovementState::Slide)
		AddMovementInput(GetActorForwardVector(), Value);
}

void AAaronCharacter::MoveRight(float Value)
{
	FVector ForwardVector = FpsCamera->GetForwardVector();
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		ForwardVector = GetActorForwardVector();

	if (CharacterMovement->IsSwimming())
		AddMovementInput(ForwardVector, Value);
	else if (MovementState != EMovementState::Slide)
		AddMovementInput(GetActorRightVector(), Value);
}

void AAaronCharacter::StartJumping()
{
	if (GetCharacterMovement()->IsFalling())
	{
		//CharacterMovement->SetMovementMode(EMovementMode::MOVE_Flying);
		if(!VaultCheck(FallingTraceSettings) && StatManager->Skills.Glider)
		{
			IsGliding = true;
			CharacterMovement->GravityScale = StatManager->GetGlidingGravityScale();
			CharacterMovement->AirControl = StatManager->GetGlidingAirControl();
			CharacterMovement->FallingLateralFriction = StatManager->GetGlidingFallingLateralFriction();
			GetWorldTimerManager().SetTimer(GliderTimerHandle, this, &AAaronCharacter::EndJumping, MaxTimeGliding);
		}
	}
	else
	{
		if (GetCharacterDirection().Size() == 0.0f || !VaultCheck(GroundedTraceSettings))
		{
			if (MovementState != EMovementState::Climb && !CharacterMovement->IsSwimming())
			{
				if (CharacterMovement->IsCrouching())
				{
					if (MovementState == EMovementState::Slide)
					{
						CharacterMovement->GroundFriction = 8.0f;
						MovementState = EMovementState::Run;
					}
					UnCrouch();
					CrouchJumped = true;
				}
				else if (StatManager->Skills.SuperJump)
				{
					bPressedJump = true;
				}
				else if (StatManager->ConsumeStamina(StatManager->GetJumpStaminaCost()))
				{
					Jump();
				}
			}
		}
	}
}

void AAaronCharacter::EndJumping()
{
	if (StatManager->Skills.SuperJump && !GetCharacterMovement()->IsFalling() && StatManager->ConsumeStamina(StatManager->GetJumpStaminaCost()))
	{
		if (bPressedJump)
		{
			GetCharacterMovement()->JumpZVelocity = StatManager->GetJumpForce() * (1.0f + 2.0f * JumpMultPercent);
			Jump();
			bPressedJump = false;
			JumpMultPercent = 0.0f;
		}
	}
	if (IsGliding)
	{
		CharacterMovement->GravityScale = StatManager->GetGravityScale();
		CharacterMovement->AirControl = StatManager->GetAirControl();
		CharacterMovement->FallingLateralFriction = 0.0f;
		IsGliding = false;
	}
}

void AAaronCharacter::ToggleCrouch()
{
	if (CanCrouch() && !CharacterMovement->IsSwimming())
	{
		if (MovementState == EMovementState::Sprint)
		{
			Crouch();
			CharacterMovement->GroundFriction = 0.f;
			SlideRotation = GetActorRotation().Vector();
			MovementState = EMovementState::Slide;
		}
		else
			Crouch();
	}
	else
	{
		if (MovementState == EMovementState::Slide)
		{
			CharacterMovement->GroundFriction = 8.0f;
			MovementState = EMovementState::Run;
		}
		UnCrouch();
	}
}

void AAaronCharacter::ToggleWalk()
{
	if (MovementState == EMovementState::Run)
		MovementState = EMovementState::Walk;
	else if (MovementState == EMovementState::Walk)
		MovementState = EMovementState::Run;
}

void AAaronCharacter::ToggleSprint()
{
	
	if (MovementState == EMovementState::Sprint)
		MovementState = EMovementState::Run;
	else if (CharacterMovement->Velocity.Size() > 0.0f)
	{
		UnCrouch();
		MovementState = EMovementState::Sprint;
	}
		
}

void AAaronCharacter::StartSprinting()
{
	UnCrouch();
	MovementState = EMovementState::Sprint;
}

void AAaronCharacter::StopSprinting()
{
	if (MovementState != EMovementState::Slide)
		MovementState = EMovementState::Run;
}


void AAaronCharacter::Dodge()
{
	FVector Direction = GetCharacterDirection();
	if (!CharacterMovement->IsFalling() && Direction.SizeSquared() != 0.0f && StatManager->ConsumeStamina(StatManager->GetDodgeStaminaCost()))
	{
		LaunchCharacter(Direction * StatManager->GetDodgeForce(), true, false);
	}
}

void AAaronCharacter::Interact()
{
	if (HitActor && HitActor->GetActor()->Implements<UObjectInteractionInterface>())
	{
		IObjectInteractionInterface::Execute_Interact(HitActor->GetActor(), true, this);
		HitActor = nullptr;
	}
}

void AAaronCharacter::StopInteract()
{
	if (HitActor && HitActor->GetActor()->Implements<UObjectInteractionInterface>())
	{
		IObjectInteractionInterface::Execute_Interact(HitActor->GetActor(), false, this);
	}
}

void AAaronCharacter::ActivateHeadEquipment()
{
	AActor* ChildActor = HeadEquipment->GetChildActor();
	if (IsValid(ChildActor) && ChildActor->Implements<UEquipmentInterface>())
		IEquipmentInterface::Execute_Activate(ChildActor, true);
}

//Left arm button pressed
void AAaronCharacter::ActivatePressedLeft()
{
	FVector ClimbPoint;
	if (SearchClimbPoint(ClimbPoint)) {
		MovementState = EMovementState::Climb;
		IsLeftHandGripping = true;
		LeftHandPosition = ClimbPoint;
		UpdateClimbingPosition();
	}
	else
	{
		AActor* ChildActor = LeftArmEquipment->GetChildActor();
		if (IsValid(ChildActor) && ChildActor->Implements<UEquipmentInterface>())
			IEquipmentInterface::Execute_Activate(ChildActor, true);
	}
}

//Left arm button released
void AAaronCharacter::ActivateReleasedLeft()
{
	if (IsLeftHandGripping)
	{
		IsLeftHandGripping = false;
		LeftHandPosition = FVector::ZeroVector;
		UpdateClimbingPosition();
	}
	else
	{
		AActor* ChildActor = LeftArmEquipment->GetChildActor();
		if (IsValid(ChildActor) && ChildActor->Implements<UEquipmentInterface>())
			IEquipmentInterface::Execute_Activate(ChildActor, false);
	}
}

//Right arm button pressed
void AAaronCharacter::ActivatePressedRight()
{
	FVector ClimbPoint;
	if (SearchClimbPoint(ClimbPoint)) {
		MovementState = EMovementState::Climb;
		IsRightHandGripping = true;
		RightHandPosition = ClimbPoint;
		UpdateClimbingPosition();
	}
	else
	{
		AActor* ChildActor = RightArmEquipment->GetChildActor();
		if (IsValid(ChildActor) && ChildActor->Implements<UEquipmentInterface>())
			IEquipmentInterface::Execute_Activate(ChildActor, true);
	}
}

//Right arm button released
void AAaronCharacter::ActivateReleasedRight()
{
	if (IsRightHandGripping)
	{
		IsRightHandGripping = false;
		RightHandPosition = FVector::ZeroVector;
		UpdateClimbingPosition();
	}
	else
	{
		AActor* ChildActor = RightArmEquipment->GetChildActor();
		if (IsValid(ChildActor) && ChildActor->Implements<UEquipmentInterface>())
			IEquipmentInterface::Execute_Activate(ChildActor, false);
	}
}

void AAaronCharacter::ActivatePressedChest()
{
	AActor* ChildActor = ChestEquipment->GetChildActor();
	if (IsValid(ChildActor) && ChildActor->Implements<UEquipmentInterface>())
		IEquipmentInterface::Execute_Activate(ChildActor, true);
}

bool AAaronCharacter::SearchClimbPoint(FVector& ClimbPoint)
{
	//Check if in range of climbing
	FHitResult HitResult;
	FVector Start = FpsCamera->GetComponentLocation();
	FVector End = Start + FpsCamera->GetForwardVector() * StatManager->GetClimbRange();
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

	//Update character state if a climbable wall is hit
	if (HitResult.IsValidBlockingHit() && HitResult.GetActor()->Implements<UClimbableInterface>())
	{
		IClimbableInterface::Execute_GetGripPoint(HitResult.GetActor(), ClimbPoint);
		return true;
	}
	else
		return false;
}


void AAaronCharacter::UpdateClimbingPosition()
{
	FVector TargetPosition = FVector::ZeroVector;

	if (IsLeftHandGripping && IsRightHandGripping)
		TargetPosition = (LeftHandPosition + RightHandPosition) / 2.0f;
	else if (IsLeftHandGripping)
		TargetPosition = LeftHandPosition;
	else if (IsRightHandGripping)
		TargetPosition = RightHandPosition;
	else
	{
		CharacterMovement->SetActive(true);
		MovementState = EMovementState::Run;
	}

	if (MovementState == EMovementState::Climb)
	{
		TargetPosition = TargetPosition - FVector(0.0f, 0.0f, 70.0f);
		CharacterMovement->SetActive(false);
		CharacterMovement->StopMovementImmediately();
		ClimbPosition = TargetPosition;
	}
}

void AAaronCharacter::Scan()
{
	FHitResult OutHit;
	FVector Start = FpsCamera->GetComponentLocation();
	FVector End = Start + FpsCamera->GetForwardVector() * RaycastDistanceInventory;
	FCollisionQueryParams collisionParams;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, collisionParams))
	{
		if (OutHit.GetActor()->Implements<UAnalyseObjectInterface>())
		{
			float ScanPercent = 0.0f;
			AMyHUD* PlayerHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			PlayerHUD->GetRadiusCircle(ScanPercent);

			if (ScanPercent < 1.0f)
				PlayerHUD->UpdateCircleRadius(ScanPercent + 0.01f);
			else
			{
				IAnalyseObjectInterface::Execute_ScanFinished(OutHit.GetActor());
				PlayerHUD->ResetCircleRadius();
			}
		}
	}
}

void AAaronCharacter::ScanRelease()
{
	AMyHUD* PlayerHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	PlayerHUD->UpdateCircleRadius(0.0f);
}

void AAaronCharacter::PressedItemWheel()
{
	CurrentTimePressedItemWheel += GetWorld()->GetDeltaSeconds();
}

void AAaronCharacter::ReleaseItemWheel()
{
	if (WheelDisplayed)
	{
		//reset wheel
		MainHudFixedSizeCPP->RemoveFromParent();

		//CloseRadialBar
		auto PlayerController = GetWorld()->GetFirstPlayerController();
		PlayerController->SetIgnoreLookInput(false);
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;

		//ChosenSlot
		HudCPP->ItemSelected = MainHudFixedSizeCPP->ChosenSlot;
	}
	else
	{
		PressedUseQuickItem();
	}

	//reset var
	CurrentTimePressedItemWheel = 0.f;
	WheelDisplayed = false;

}

void AAaronCharacter::DisplayWheel()
{
	MainHudFixedSizeCPP->AddToViewport();
	MainHudFixedSizeCPP->CreateStandartWidgetCPP();

	//Open Radial Bar
	auto PlayerController = GetWorld()->GetFirstPlayerController();

	FInputModeGameAndUI InputModeData;
	InputModeData.SetWidgetToFocus(MainHudFixedSizeCPP->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->SetIgnoreLookInput(true);
	PlayerController->bShowMouseCursor = true;
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	PlayerController->SetMouseLocation(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
}

void AAaronCharacter::UseMyItem(UDA_SlotStructure* ChosenSlot)
{
	if (IsValid(ChosenSlot) && IsValid(ChosenSlot->ItemStructure))
	{
		if (ChosenSlot->ItemStructure->IsConsomable)
		{
			FTransform* transform = new FTransform();
			transform->SetScale3D(FVector(0.1, 0.1, 0.1));
			AItem* item = (AItem*)GetWorld()->SpawnActor(ChosenSlot->ItemStructure->Class.Get(), transform, FActorSpawnParameters());
			bool bItemUsed = item->UseItem();
			item->Destroy();
			if (bItemUsed)
			{
				//Log de slotitem . display name
				if (ChosenSlot->Quantity == 1)
				{
					//remove slot
					ChosenSlot->Quantity = 0;
					InventaireComponent->RemoveFromInventory(ChosenSlot);
				}
				else
				{
					ChosenSlot->Quantity--;
				}
			}
		}
	}
}

void AAaronCharacter::PressedUseQuickItem()
{
	if (IsValid(MainHudFixedSizeCPP->ChosenSlot) && MainHudFixedSizeCPP->ChosenSlot->Quantity > 0)
	{
		UseMyItem(MainHudFixedSizeCPP->ChosenSlot);
	}
}

FVector AAaronCharacter::GetCapsuleBaseLocation(float ZOffset) const
{
	return GetCapsuleComponent()->GetComponentLocation() - ((GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + ZOffset) * GetCapsuleComponent()->GetUpVector());
}

FVector AAaronCharacter::GetCapsuleBaseLocationFromBase(FVector BaseLocation, float ZOffset) const
{
	return FVector(BaseLocation.X, BaseLocation.Y, BaseLocation.Z + GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + ZOffset);
}

void AAaronCharacter::UpdateTimelineFunction(float value)
{
	FTransform VaultTarget = VaultLedgeWS.Transform;//ConvertLocalToWorld(VaultLedgeLS).Transform;
	FVector VectorOfCurve = VaultParams.PositionCurve->GetVectorValue(VaultTimeline->GetPlaybackPosition() + VaultParams.StartingPosition);
	FTransform BlendTrans = FTransform(VaultAnimatedStartOffset.GetRotation(), FVector(VaultAnimatedStartOffset.GetLocation().X, VaultAnimatedStartOffset.GetLocation().Y, VaultStartOffset.GetLocation().Z));
	FTransform XYCorrectionTrans = UKismetMathLibrary::TLerp(VaultStartOffset, BlendTrans, VectorOfCurve.Y);
	FTransform ZCorrectionTrans = UKismetMathLibrary::TLerp(VaultStartOffset, BlendTrans, VectorOfCurve.Z);

	FTransform LerpTrans = FTransform(XYCorrectionTrans.GetRotation(), FVector(XYCorrectionTrans.GetLocation().X, XYCorrectionTrans.GetLocation().Y, ZCorrectionTrans.GetLocation().Z));
	FTransform Transform = UKismetMathLibrary::TLerp(VaultTarget + LerpTrans, VaultTarget, VectorOfCurve.Y);
	LerpTrans = UKismetMathLibrary::TLerp(VaultTarget + VaultStartOffset, Transform, value);

	SetActorLocationAndRotation(LerpTrans.GetLocation(), LerpTrans.GetRotation());
}

void AAaronCharacter::EndTimelineFunction()
{
	CanVault = false;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AAaronCharacter::UpdateBindAction()
{
	auto PlayerInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (PlayerInputComponent)
	{
		if (UserSettings->GetIsToggleSprint())
		{
			PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AAaronCharacter::ToggleSprint);
		}
		else
		{
			PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AAaronCharacter::StartSprinting);
			PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AAaronCharacter::StopSprinting);
		}
	}/*else
	{
		UE_LOG(LogActor, Error, TEXT("PlayerInput null"));
	}*/
	
}

bool AAaronCharacter::VaultCheck(VaultTraceSettings TraceSettings)
{
	VaultType VaultType;
	FVector InitialTraceImpactPoint;
	FVector InitialTraceNormal;
	float VaultHeight;

	if (FindWallToClimb(TraceSettings, InitialTraceImpactPoint, InitialTraceNormal))
	{
		if (CanClimbOnWall(TraceSettings, InitialTraceImpactPoint, InitialTraceNormal, VaultHeight, VaultType))
		{
			VaultStart(VaultHeight, VaultType);
			return true;
		}
	}

	return false;
}

void AAaronCharacter::VaultStart(float VaultHeight, VaultType VaultType)
{
	VaultParams = GetVaultParam(VaultType, VaultHeight);
	VaultLedgeLS = ConvertWorldToLocal(VaultLedgeWS);
	VaultStartOffset = GetVaultStartOffset(VaultLedgeWS.Transform);
	VaultAnimatedStartOffset = GetVaultAnimatedStartOffset(VaultParams, VaultLedgeWS.Transform);

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	float MaxTime, MinTime;
	VaultParams.PositionCurve->GetTimeRange(MinTime, MaxTime);
	VaultTimeline->SetTimelineLength(MaxTime - VaultParams.StartingPosition);
	VaultTimeline->SetPlayRate(VaultParams.PlayRate);
	VaultTimeline->PlayFromStart();

	CanVault = true;
}

bool AAaronCharacter::FindWallToClimb(VaultTraceSettings TraceSettings, FVector& InitialTraceImpactPoint, FVector& InitialTraceNormal)
{
	FVector Start = GetCapsuleBaseLocation(2.0f) + GetCharacterDirection() * (-30);
	Start.Z += (TraceSettings.MaxLedgeHeight + TraceSettings.MinLedgeHeight) / 2.0f;
	FVector End = Start + GetCharacterDirection() * TraceSettings.Distance;
	FHitResult OutHit;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FCollisionShape CapsuleShape = FCollisionShape();
	//CapsuleShape.MakeCapsule(TraceSettings.ForwardTraceRadius, (TraceSettings.MaxLedgeHeight - TraceSettings.MinLedgeHeight) / 2.0f + 1.0f);
	CapsuleShape.MakeCapsule(TraceSettings.ForwardTraceRadius, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	
	if (GetWorld()->SweepSingleByChannel(OutHit, Start, End, FQuat::Identity, ECC_GameTraceChannel2, CapsuleShape, CollisionParams))
	{
		if (/*GetCharacterMovement()->IsWalkable(OutHit) &&*/ !OutHit.bStartPenetrating)
		{
			InitialTraceImpactPoint = OutHit.ImpactPoint;
			InitialTraceNormal = OutHit.ImpactNormal;
			return true;
		}
	}
	return false;
}

bool AAaronCharacter::CanClimbOnWall(VaultTraceSettings TraceSettings, FVector& InitialTraceImpactPoint, FVector& InitialTraceNormal, float& VaultHeight, VaultType& Vault)
{
	FVector DownTraceLocation;

	FVector End = FVector(InitialTraceImpactPoint.X, InitialTraceImpactPoint.Y, GetCapsuleBaseLocation(2.0f).Z) + InitialTraceNormal * (-15.0f);
	FVector Start = FVector(End.X, End.Y, GetActorLocation().Z + TraceSettings.MaxLedgeHeight + TraceSettings.DownwardTraceRadius + 1.0f);
	FHitResult OutHit;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.bDebugQuery = true;

	FCollisionShape CapsuleShape = FCollisionShape();
	//CapsuleShape.MakeSphere(TraceSettings.DownwardTraceRadius);
	CapsuleShape.MakeCapsule(TraceSettings.DownwardTraceRadius, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	if (GetWorld()->SweepSingleByChannel(OutHit, Start, End, FQuat::Identity, ECC_GameTraceChannel2, CapsuleShape, CollisionParams))
	{
		if (GetCharacterMovement()->IsWalkable(OutHit))
		{
			DownTraceLocation = FVector(OutHit.Location.X, OutHit.Location.Y, OutHit.ImpactPoint.Z);
			if (CapsuleHasRoomCheck(GetCapsuleBaseLocationFromBase(DownTraceLocation, 2.0f), 0.0f, 0.0f))
			{
				FVector toRot = InitialTraceNormal * FVector(-1.0f, -1.0f, 0.0f);
				FTransform Transform = FTransform(toRot.Rotation(), GetCapsuleBaseLocationFromBase(DownTraceLocation, 2.0f), FVector::OneVector);
				VaultLedgeWS = FVaultComponentAndTransform(OutHit.GetComponent(), Transform);
				VaultHeight = (Transform.GetLocation() - GetActorLocation()).Z;

				if (!GetCharacterMovement()->IsFalling())
				{
					if (VaultHeight > 125.0f)
						Vault = VaultType::HighVault;
					else
						Vault = VaultType::LowVault;
				}
				else
					Vault = VaultType::FallingCatch;

				return true;
			}
		}
	}
	return false;
}

bool AAaronCharacter::CapsuleHasRoomCheck(FVector TargetLocation, float HeightOffset, float RadiusOffset)
{
	float ZValue = GetCapsuleComponent()->GetScaledCapsuleHalfHeight_WithoutHemisphere() + RadiusOffset * (-1.0f) + HeightOffset;
	FVector Start = TargetLocation + FVector(0, 0, ZValue);
	FHitResult OutHit;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FCollisionShape CapsuleShape = FCollisionShape();
	CapsuleShape.MakeSphere(GetCapsuleComponent()->GetScaledCapsuleRadius() + RadiusOffset);

	return !(GetWorld()->SweepSingleByChannel(OutHit, Start, Start, FpsCamera->GetComponentRotation().Quaternion(), ECC_GameTraceChannel2, CapsuleShape, CollisionParams) || OutHit.bStartPenetrating);
}

FVaultComponentAndTransform AAaronCharacter::ConvertWorldToLocal(FVaultComponentAndTransform WorldSpaceVault)
{
	FTransform TransformLocal = WorldSpaceVault.Transform * WorldSpaceVault.Component->GetComponentTransform().Inverse();
	return  FVaultComponentAndTransform(WorldSpaceVault.Component, TransformLocal);
}

FVaultComponentAndTransform AAaronCharacter::ConvertLocalToWorld(FVaultComponentAndTransform LocalSpaceVault)
{
	FTransform TransformWorld = LocalSpaceVault.Transform * LocalSpaceVault.Component->GetComponentTransform();
	return FVaultComponentAndTransform(LocalSpaceVault.Component, TransformWorld);
}

FVaultParams AAaronCharacter::GetVaultParam(VaultType Vault, float VaultHeight)
{
	FVaultAsset VaultAsset;
	switch (Vault)
	{
	case VaultType::LowVault:
		VaultAsset = LowVaultAsset;
		break;
	case VaultType::HighVault:
		VaultAsset = HightVaultAsset;
		break;
	case VaultType::FallingCatch:
		VaultAsset = FallingVaultAsset;
	}

	float PlayRate = UKismetMathLibrary::MapRangeClamped(VaultHeight, VaultAsset.LowHeight, VaultAsset.HightHeight, VaultAsset.LowPlayRate, VaultAsset.HightPlayRate);
	float StartingPos = UKismetMathLibrary::MapRangeClamped(VaultHeight, VaultAsset.LowHeight, VaultAsset.HightHeight, VaultAsset.LowStartPosition, VaultAsset.HightStartPosition);

	return FVaultParams(VaultAsset, PlayRate, StartingPos);

}

FTransform AAaronCharacter::GetVaultStartOffset(FTransform& VaultTarget)
{
	FTransform OutputTransform;
	OutputTransform.SetLocation(GetActorTransform().GetLocation() - VaultTarget.GetLocation());
	OutputTransform.SetRotation(GetActorTransform().GetRotation() - VaultTarget.GetRotation());
	OutputTransform.SetScale3D(GetActorTransform().GetScale3D() - VaultTarget.GetScale3D());
	return  OutputTransform;
}

FTransform AAaronCharacter::GetVaultAnimatedStartOffset(FVaultParams& VaultParam, FTransform& VaultTarget)
{
	FVector blbl = VaultTarget.GetRotation().GetAxisX() * VaultParam.StartingOffset.Y;
	blbl.Z = VaultParam.StartingOffset.Z;
	FTransform Transform = FTransform(VaultTarget.GetRotation(), VaultTarget.GetLocation() - blbl, FVector::OneVector);

	FTransform OutputTransform;
	OutputTransform.SetLocation(Transform.GetLocation() - VaultTarget.GetLocation());
	OutputTransform.SetRotation(Transform.GetRotation() - VaultTarget.GetRotation());
	OutputTransform.SetScale3D(Transform.GetScale3D() - VaultTarget.GetScale3D());
	return  OutputTransform;

}