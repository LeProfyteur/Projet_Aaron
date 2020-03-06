// Fill out your copyright notice in the Description page of Project Settings.


#include "AaronCharacter.h"

// Sets default values
AAaronCharacter::AAaronCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FpsCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_Camera"));
	FpsCamera->SetupAttachment(RootComponent);
	FpsCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FpsCamera->bUsePawnControlRotation = true;

	StatManager = CreateDefaultSubobject<UCharacterStatManager>(TEXT("StatManager"));

	CharacterMovement = GetCharacterMovement();
	CharacterMovement->JumpZVelocity = StatManager->GetJumpForce();
	CharacterMovement->GetNavAgentPropertiesRef().bCanCrouch = true;

	RightArmEquipment = CreateDefaultSubobject<UChildActorComponent>(TEXT("Right Arm Equipment"));
	RightArmEquipment->SetupAttachment(FpsCamera);

	LeftArmEquipment = CreateDefaultSubobject<UChildActorComponent>(TEXT("Left Arm Equipment"));
	LeftArmEquipment->SetupAttachment(FpsCamera);

	HeadEquipment = CreateDefaultSubobject<UChildActorComponent>(TEXT("Head Equipment"));
	HeadEquipment->SetupAttachment(FpsCamera);

	InventaireComponent = CreateDefaultSubobject<UInventaireComponent>(TEXT("InventaireComponent"));
	InventaireComponent->PrepareInventory();
}

// Called when the game starts or when spawned
void AAaronCharacter::BeginPlay()
{
	Super::BeginPlay();
	MovementState = EMovementState::Run;
}

// Called every frame
void AAaronCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementState == EMovementState::Sprint && CharacterMovement->Velocity.Size() > 0.0f)
	{
		if (!StatManager->ConsumeStamina(StatManager->GetSprintStaminaCost()))
			MovementState = EMovementState::Run;
	}

	if (MovementState == EMovementState::Slide && CharacterMovement->Velocity.Size() <= 0.0f)
	{
		CharacterMovement->GroundFriction = 8.0f;
		MovementState = EMovementState::Run;
	}
		
	if (MovementState == EMovementState::Climb)
		Climb(DeltaTime);
	else
		UpdateSpeed();

	StatManager->RecoveryStamina(DeltaTime);

	//itemWheel
	if (CurrentTimePressedItemWheel > 0.f)
	{
		CurrentTimePressedItemWheel += DeltaTime;
		if (!WheelDisplayed && CurrentTimePressedItemWheel >= HoldingTimeItemWheel)
		{
			DisplayWheel();
			WheelDisplayed = true;
		}
	}

	//Detecting pickable objects
	/*FHitResult OutHit;
	FVector Start = FpsCamera->GetComponentLocation();
	FVector End = Start + FpsCamera->GetForwardVector() * RaycastDistanceInventory;
	FCollisionQueryParams collisionParams;

	if (GetWorld()->SweepSingleByChannel(OutHit, Start, End, FpsCamera->GetComponentRotation().Quaternion(), ECC_Visibility, FCollisionShape::MakeCapsule(50, 50), collisionParams))
	{
		UStaticMeshComponent* actorMeshComponent = OutHit.Actor->FindComponentByClass<UStaticMeshComponent>();
		if (OutHit.GetActor()->Implements<UObjectInteractionInterface>())
		{
			//UE_LOG(LogActor, Warning, TEXT("%s"), *IObjectInteractionInterface::Execute_GetLabel(OutHit.GetActor()));
			if (!HitActor || OutHit.Actor != HitActor->Actor)
				HitActor = new FHitResult(OutHit);

			InventoryCastObject->nameTextItem = IObjectInteractionInterface::Execute_GetLabel(OutHit.GetActor()) + " [F]";
		}
		else
		{
			InventoryCastObject->nameTextItem = "";
		}
	}
	else if (HitActor)
	{
		UStaticMeshComponent* actorMeshComponent = HitActor->Actor->FindComponentByClass<UStaticMeshComponent>();
		actorMeshComponent->SetCustomDepthStencilValue(1);
		InventoryCastObject->nameTextItem = "";
		HitActor = nullptr;
	}*/
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
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AAaronCharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AAaronCharacter::StartSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AAaronCharacter::StopSprinting);

	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &AAaronCharacter::Walking);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AAaronCharacter::Crouching);

	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AAaronCharacter::Dodge);
	
	PlayerInputComponent->BindAction("FireLeft", IE_Pressed, this, &AAaronCharacter::ActivatePressedLeft);
	PlayerInputComponent->BindAction("FireLeft", IE_Released, this, &AAaronCharacter::ActivateReleasedLeft);

	PlayerInputComponent->BindAction("FireRight", IE_Pressed, this, &AAaronCharacter::ActivatePressedRight);
	PlayerInputComponent->BindAction("FireRight", IE_Released, this, &AAaronCharacter::ActivateReleasedRight);

	PlayerInputComponent->BindAction("HeadAction", IE_Pressed, this, &AAaronCharacter::ActivateHeadEquipment);

	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AAaronCharacter::Action);
	PlayerInputComponent->BindAction("Action", IE_Released, this, &AAaronCharacter::StopAction);

	PlayerInputComponent->BindAction("ItemWheel", IE_Pressed, this, &AAaronCharacter::PressedItemWheel);
	PlayerInputComponent->BindAction("ItemWheel", IE_Repeat, this, &AAaronCharacter::RepeatItemWheel);
	PlayerInputComponent->BindAction("ItemWheel", IE_Released, this, &AAaronCharacter::ReleaseItemWheel);
}

void AAaronCharacter::Climb(float DeltaTime)
{
	FVector LerpPosition = FMath::Lerp(GetActorLocation(), ClimbPosition, StatManager->GetClimbSpeed());
	SetActorLocation(LerpPosition);
}

void AAaronCharacter::UpdateSpeed()
{
	float Multiplier = StatManager->GetSpeedMultiplier();
	UCharacterMovementComponent* CM = CharacterMovement;
	switch(MovementState)
	{
	case EMovementState::Run:
		CM->MaxWalkSpeed = StatManager->GetRunSpeed() * Multiplier;
		CM->MaxWalkSpeedCrouched = StatManager->GetCrouchRunSpeed() * Multiplier;
		CM->MaxSwimSpeed = StatManager->GetSwimmingSpeed() * Multiplier;
		break;
	case EMovementState::Walk:
		CM->MaxWalkSpeed = StatManager->GetWalkSpeed() * Multiplier;
		CM->MaxWalkSpeedCrouched = StatManager->GetCrouchWalkSpeed() * Multiplier;
		CM->MaxSwimSpeed = StatManager->GetSwimmingSpeed() * Multiplier;
		break;
	case EMovementState::Sprint:
		CM->MaxWalkSpeed = StatManager->GetSprintSpeed() * Multiplier;
		CM->MaxWalkSpeedCrouched = StatManager->GetCrouchRunSpeed() * Multiplier;
		CM->MaxSwimSpeed = StatManager->GetSwimmingSprintSpeed() * Multiplier;
		break;
	default: ;
	}
}

FVector AAaronCharacter::GetCharacterDirection() const
{
	FVector Direction = GetInputAxisValue("MoveForward") * GetActorForwardVector() + GetInputAxisValue("MoveRight") * GetActorRightVector() * GetActorUpVector();
	Direction.Normalize();
	return Direction;
}

void AAaronCharacter::MoveForward(float Value)
{
	if (MovementState != EMovementState::Slide)
		AddMovementInput(GetActorForwardVector(), Value);
}

void AAaronCharacter::MoveRight(float Value)
{
	if (MovementState != EMovementState::Slide)
		AddMovementInput(GetActorRightVector(), Value);
}

void AAaronCharacter::StartJumping()
{
	//if (MovementState == EMovementState::Slide)
	if (MovementState != EMovementState::Climb && !CharacterMovement->IsFalling() && StatManager->ConsumeStamina(StatManager->GetJumpStaminaCost()))
	{
	
		UnCrouch();
		Jump();
	}
}

void AAaronCharacter::Walking()
{
	if (MovementState == EMovementState::Run)
		MovementState = EMovementState::Walk;
	else if (MovementState == EMovementState::Walk)
		MovementState = EMovementState::Run;
}

void AAaronCharacter::Crouching()
{
	if (CanCrouch())
	{
		if (MovementState == EMovementState::Sprint)
		{
			Crouch();
			CharacterMovement->GroundFriction = 0.f;
			MovementState = EMovementState::Slide;
			LaunchCharacter(GetCharacterDirection() * 3000.0f, true, true);
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

void AAaronCharacter::Action()
{
	if (HitActor && HitActor->GetActor()->Implements<UObjectInteractionInterface>())
	{
		UDA_ItemStructure* ItemStructure = NewObject<UDA_ItemStructure>(UDA_ItemStructure::StaticClass());
		IObjectInteractionInterface::Execute_Interact(HitActor->GetActor(), true, ItemStructure, this);
		if (ItemStructure->Name != "")
		{
			UE_LOG(LogActor, Warning, TEXT("Add to inventory : %s"), *ItemStructure->Name);
			InventaireComponent->AddToInventory(ItemStructure);
		}
		else
		{
			UE_LOG(LogActor, Error, TEXT("Error add to inventory"));
		}
		HitActor = nullptr;
	}
}

void AAaronCharacter::StopAction()
{
	if (HitActor && HitActor->GetActor()->Implements<UObjectInteractionInterface>())
	{
		IObjectInteractionInterface::Execute_Interact(HitActor->GetActor(), false, nullptr, this);
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

void AAaronCharacter::PressedItemWheel()
{
	UE_LOG(LogActor, Warning, TEXT("Item wheel Pressed"));
	CurrentTimePressedItemWheel += GetWorld()->GetDeltaSeconds();
}

void AAaronCharacter::RepeatItemWheel()
{
	UE_LOG(LogActor, Warning, TEXT("Item wheel Repeat"));
}


void AAaronCharacter::ReleaseItemWheel()
{
	UE_LOG(LogActor, Warning, TEXT("Item wheel Released"));


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
			transform->SetScale3D(FVector(0., 0., 0.));
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
	UE_LOG(LogActor, Warning, TEXT("Use Quick Item"));

	if (IsValid(MainHudFixedSizeCPP->ChosenSlot) && MainHudFixedSizeCPP->ChosenSlot->Quantity > 0)
	{
		UseMyItem(MainHudFixedSizeCPP->ChosenSlot);
	}
}