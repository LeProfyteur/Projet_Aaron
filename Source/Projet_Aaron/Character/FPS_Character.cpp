// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_Character.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Engine.h"
#include "MyHUD.h"
//UMG
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Projet_Aaron/Item/Item.h"
#include "Projet_Aaron/Equipment/EquipmentInterface.h"

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

	InventaireComponent = CreateDefaultSubobject<UInventaireComponent>(TEXT("InventaireComponent"));
	InventaireComponent->PrepareInventory();
}

// Called when the game starts or when spawned
void AFPS_Character::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(InventaireComponent))
	{
		UE_LOG(LogActor, Warning, TEXT("Name Inventaire : %s"), *InventaireComponent->InventoryName);
	}else
	{
		UE_LOG(LogActor, Error, TEXT("Name Inventaire : undefined"));
	}	
}

// Called every frame
void AFPS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsClimbing)
		CharacterClimb(DeltaTime);
	else
		CharacterMove();

	StatManager->RecoveryStamina(DeltaTime);

	//itemWheel
	if(CurrentTimePressedItemWheel>0.f)
	{
		CurrentTimePressedItemWheel += DeltaTime;
		if (!WheelDisplayed && CurrentTimePressedItemWheel >= HoldingTimeItemWheel)
		{
			DisplayWheel();
			WheelDisplayed = true;
		}
	}

	FHitResult OutHit;
	FVector Start = FpsCamera->GetComponentLocation();
	FVector End = Start + FpsCamera->GetForwardVector() * RaycastDistanceInventory;
	FCollisionQueryParams collisionParams;
	
	if (GetWorld()->SweepSingleByChannel(OutHit, Start, End, FpsCamera->GetComponentRotation().Quaternion(), ECC_Visibility, FCollisionShape::MakeCapsule(50, 50), collisionParams))
	{
		UStaticMeshComponent* actorMeshComponent = OutHit.Actor->FindComponentByClass<UStaticMeshComponent>();
		if(OutHit.GetActor()->Implements<UObjectInteractionInterface>())
		{
			//UE_LOG(LogActor, Warning, TEXT("%s"), *IObjectInteractionInterface::Execute_GetLabel(OutHit.GetActor()));
			if (!HitActor || OutHit.Actor != HitActor->Actor)
				HitActor = new FHitResult(OutHit);
			
			InventoryCastObject->nameTextItem = IObjectInteractionInterface::Execute_GetLabel(OutHit.GetActor()) + " [F]";
		}else
		{
			InventoryCastObject->nameTextItem = "";
		}
	} else if(HitActor)
	{
		UStaticMeshComponent* actorMeshComponent = HitActor->Actor->FindComponentByClass<UStaticMeshComponent>();
		actorMeshComponent->SetCustomDepthStencilValue(1);
		InventoryCastObject->nameTextItem = "";
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
	PlayerInputComponent->BindAction("Action", IE_Released,this, &AFPS_Character::StopAction);

	//PlayerInputComponent->BindAction("UseQuickItem", IE_Pressed, this, &AFPS_Character::PressedUseQuickItem);
	PlayerInputComponent->BindAction("ItemWheel", IE_Pressed, this, &AFPS_Character::PressedItemWheel);
	PlayerInputComponent->BindAction("ItemWheel", IE_Repeat, this, &AFPS_Character::RepeatItemWheel);
	PlayerInputComponent->BindAction("ItemWheel", IE_Released, this, &AFPS_Character::ReleaseItemWheel);

}

void AFPS_Character::CharacterMove()
{
	FVector Direction = GetActorForwardVector() * ForwardAxisMovement + GetActorRightVector() * RightAxisMovement;
	if (bPressedAlt)
	{
		Dodge(Direction);
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

void AFPS_Character::CharacterClimb(float DeltaTime)
{
	FVector LerpPosition = FMath::Lerp(GetActorLocation(), ClimbPosition, ClimbLerpSpeed);
	SetActorLocation(LerpPosition);
}

bool AFPS_Character::SearchClimbPoint(FVector& ClimbPoint)
{
	//Check if in range of climbing
	FHitResult HitResult;
	FVector Start = FpsCamera->GetComponentLocation();
	FVector End = Start + FpsCamera->GetForwardVector() * ClimbRange;
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


void AFPS_Character::UpdateClimbingPosition()
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
		GetCharacterMovement()->SetActive(true);
		IsClimbing = false;
	}

	if (IsClimbing)
	{
		TargetPosition = TargetPosition - FVector(0.0f, 0.0f, 70.0f);
		GetCharacterMovement()->SetActive(false);
		GetCharacterMovement()->StopMovementImmediately();
		ClimbPosition = TargetPosition;
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
	if(!GetCharacterMovement()->IsFalling() && StatManager->ConsumeStamina(StatManager->GetJumpStaminaCost()) && !IsClimbing)
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
	if (HitActor && HitActor->GetActor()->Implements<UObjectInteractionInterface>())
	{
		UDA_ItemStructure* ItemStructure = NewObject<UDA_ItemStructure>(UDA_ItemStructure::StaticClass());
		IObjectInteractionInterface::Execute_Interact(HitActor->GetActor(), true, ItemStructure, this);
		if(IsValid(ItemStructure))
		{
			UE_LOG(LogActor, Warning, TEXT("Add to inventory : %s"), *ItemStructure->Name);
			InventaireComponent->AddToInventory(ItemStructure);
		}else
		{
			UE_LOG(LogActor, Error, TEXT("Error add to inventory"));
		}
		HitActor = nullptr;
	}
}

void AFPS_Character::StopAction()
{
	if (HitActor && HitActor->GetActor()->Implements<UObjectInteractionInterface>())
	{
		IObjectInteractionInterface::Execute_Interact(HitActor->GetActor(), false, nullptr,this);
	}
}

//Left arm button pressed
void AFPS_Character::ActivatePressedLeft()
{
	FVector ClimbPoint;
	if (SearchClimbPoint(ClimbPoint)) {
			IsClimbing = true;
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
void AFPS_Character::ActivateReleasedLeft()
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
void AFPS_Character::ActivatePressedRight()
{
	FVector ClimbPoint;
	if (SearchClimbPoint(ClimbPoint)) {
		IsClimbing = true;
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
void AFPS_Character::ActivateReleasedRight()
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

//Head button pressed
void AFPS_Character::ActivateHeadEquipment()
{
	AActor* ChildActor = HeadEquipment->GetChildActor();
	if (IsValid(ChildActor) && ChildActor->Implements<UEquipmentInterface>())
		IEquipmentInterface::Execute_Activate(ChildActor, true);
}

void AFPS_Character::PressedItemWheel()
{
	UE_LOG(LogActor, Warning, TEXT("Item wheel Pressed"));
	CurrentTimePressedItemWheel += GetWorld()->GetDeltaSeconds();
}

void AFPS_Character::RepeatItemWheel()
{
	UE_LOG(LogActor, Warning, TEXT("Item wheel Repeat"));
}


void AFPS_Character::ReleaseItemWheel()
{
	UE_LOG(LogActor, Warning, TEXT("Item wheel Released"));
	

	if(WheelDisplayed)
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
	}else
	{
		PressedUseQuickItem();
	}

	//reset var
	CurrentTimePressedItemWheel = 0.f;
	WheelDisplayed = false;

}

void AFPS_Character::DisplayWheel()
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

void AFPS_Character::UseMyItem(UDA_SlotStructure* ChosenSlot)
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

void AFPS_Character::PressedUseQuickItem()
{
	UE_LOG(LogActor, Warning, TEXT("Use Quick Item"));

	if (IsValid(MainHudFixedSizeCPP->ChosenSlot) && MainHudFixedSizeCPP->ChosenSlot->Quantity > 0)
	{
		UseMyItem(MainHudFixedSizeCPP->ChosenSlot);
	}
}

void AFPS_Character::ResetAdrenalineBoost()
{
	StatManager->SetbAdrenalineBoost(false);
}
