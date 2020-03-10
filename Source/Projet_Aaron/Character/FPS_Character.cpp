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
#include "Kismet/KismetMathLibrary.h"

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
	
	VaultTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Vault Timeline"));
	
	UpdateTimeline.BindUFunction(this, FName("UpdateTimelineFunction"));
	FinishTimeLine.BindUFunction(this, FName("EndTimelineFunction"));
	
	CurrentStateMovement = EStateMovement::Run;
}

// Called when the game starts or when spawned
void AFPS_Character::BeginPlay()
{
	Super::BeginPlay();
	VaultTimeline->AddInterpFloat(CurveFloat, UpdateTimeline);
	VaultTimeline->SetTimelineFinishedFunc(FinishTimeLine);
}

// Called every frame
void AFPS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentStateMovement == EStateMovement::Sprint && GetCharacterMovement()->Velocity.SizeSquared() > 0.0f)
	{
		if (!StatManager->ConsumeStamina(StatManager->GetSprintStaminaCost()))
			StopSprint();
	}

	if (IsClimbing)
		CharacterClimb(DeltaTime);

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
			actorMeshComponent->SetCustomDepthStencilValue(3);
			//UE_LOG(LogActor, Warning, TEXT("%s"), *IObjectInteractionInterface::Execute_GetLabel(OutHit.GetActor()));
			if (!HitActor || OutHit.Actor != HitActor->Actor)
				HitActor = new FHitResult(OutHit);
			
			InventoryCastObject->nameTextItem = IObjectInteractionInterface::Execute_GetLabel(OutHit.GetActor()) + " [F]";
		}
		else if (OutHit.GetActor()->Implements<UAnalyseObjectInterface>())
		{
			actorMeshComponent->SetCustomDepthStencilValue(3);
			if (!HitActor || OutHit.Actor != HitActor->Actor)
				HitActor = new FHitResult(OutHit);
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

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPS_Character::MoveCharacter<EMovement::Forward>);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPS_Character::MoveCharacter<EMovement::Right>);

	PlayerInputComponent->BindAxis("Turn", this, &AFPS_Character::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPS_Character::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPS_Character::StartJump);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFPS_Character::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFPS_Character::StopSprint);

	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AFPS_Character::Dodge);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFPS_Character::Crouching);
	
	PlayerInputComponent->BindAction("FireLeft", IE_Pressed,this, &AFPS_Character::ActivatePressedLeft);
	PlayerInputComponent->BindAction("FireLeft", IE_Released,this, &AFPS_Character::ActivateReleasedLeft);

	PlayerInputComponent->BindAction("FireRight", IE_Pressed, this, &AFPS_Character::ActivatePressedRight);
	PlayerInputComponent->BindAction("FireRight", IE_Released, this, &AFPS_Character::ActivateReleasedRight);
	
	PlayerInputComponent->BindAction("HeadAction", IE_Pressed, this, &AFPS_Character::ActivateHeadEquipment);
	
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AFPS_Character::Action);
	PlayerInputComponent->BindAction("Action", IE_Released,this, &AFPS_Character::StopAction);
	
	PlayerInputComponent->BindAction("ItemWheel", IE_Pressed, this, &AFPS_Character::PressedItemWheel);
	PlayerInputComponent->BindAction("ItemWheel", IE_Repeat, this, &AFPS_Character::RepeatItemWheel);
	PlayerInputComponent->BindAction("ItemWheel", IE_Released, this, &AFPS_Character::ReleaseItemWheel);

}

FVector AFPS_Character::GetPlayerInput() const
{
	FVector Direction = GetInputAxisValue("MoveForward") * GetActorForwardVector() + GetInputAxisValue("MoveRight") * GetActorRightVector();
	Direction.Normalize();
	return  Direction;
}

template <EMovement EMovementCharacter>
void AFPS_Character::MoveCharacter(float AxisValue)
{
	switch (EMovementCharacter)
	{
	case EMovement::Forward:
		AddMovementInput(GetActorForwardVector(), AxisValue);
		break;

	case EMovement::Right:
		AddMovementInput(GetActorRightVector(), AxisValue);
		break;

	default:
		UE_LOG(LogActor, Error, TEXT("Default"));
		break;
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

FVector AFPS_Character::GetCapsuleBaseLocation(float ZOffset) const
{
	return GetCapsuleComponent()->GetComponentLocation() - ((GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + ZOffset) * GetCapsuleComponent()->GetUpVector());
}

FVector AFPS_Character::GetCapsuleBaseLocationFromBase(FVector BaseLocation, float ZOffset) const
{
	return FVector(BaseLocation.X, BaseLocation.Y, BaseLocation.Z + GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + ZOffset);
}

void AFPS_Character::UpdateTimelineFunction(float value)
{
	FTransform VaultTarget = ConvertLocalToWorld(VaultLedgeLS).Transform;
	FVector VectorOfCurve = VaultParams.PositionCurve->GetVectorValue(VaultTimeline->GetPlaybackPosition() + VaultParams.StartingPosition);
	FTransform BlendTrans = FTransform(VaultAnimatedStartOffset.GetRotation(), FVector(VaultAnimatedStartOffset.GetLocation().X, VaultAnimatedStartOffset.GetLocation().Y, VaultStartOffset.GetLocation().Z));
	FTransform XYCorrectionTrans =  UKismetMathLibrary::TLerp(VaultStartOffset, BlendTrans, VectorOfCurve.Y);
	FTransform ZCorrectionTrans = UKismetMathLibrary::TLerp(VaultStartOffset, BlendTrans, VectorOfCurve.Z);

	FTransform LerpTrans = FTransform(XYCorrectionTrans.GetRotation(), FVector(XYCorrectionTrans.GetLocation().X, XYCorrectionTrans.GetLocation().Y, ZCorrectionTrans.GetLocation().Z));
	FTransform Transform = UKismetMathLibrary::TLerp(VaultTarget + LerpTrans, VaultTarget, VectorOfCurve.Y);
	LerpTrans = UKismetMathLibrary::TLerp(VaultTarget + VaultStartOffset, Transform, value);

	SetActorLocationAndRotation(LerpTrans.GetLocation(), LerpTrans.GetRotation());
}

void AFPS_Character::EndTimelineFunction()
{
	CanVault = false;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
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

void AFPS_Character::StartJump()
{
	bool res = false;
	if (GetCharacterMovement()->IsFalling())
	{
		res = VaultCheck(FallingTraceSettings);
	}
	else
	{
		if(GetPlayerInput().Size() != 0.0f)
			res = VaultCheck(GroundedTraceSettings);
		if (!res && StatManager->ConsumeStamina(StatManager->GetJumpStaminaCost()) && !IsClimbing)
			if (!GetCharacterMovement()->IsCrouching())
				Jump();
			else
				UnCrouch();
	}

	UE_LOG(LogActor, Error, TEXT("FPS_Character::StartJump : VaultCheck = %d"), res);
}

void AFPS_Character::Sprint()
{
	StatManager->SetActualSpeed(StatManager->GetSprintSpeed());
	CurrentStateMovement = EStateMovement::Sprint;
}

void AFPS_Character::StopSprint()
{
	StatManager->ResetSpeed();
	CurrentStateMovement = EStateMovement::Run;
}

void AFPS_Character::Dodge()
{
	FVector Direction = GetPlayerInput();
	if (!GetCharacterMovement()->IsFalling() && Direction.SizeSquared() != 0.0f && StatManager->ConsumeStamina(StatManager->GetDodgeStaminaCost()))
	{
		LaunchCharacter(Direction * StatManager->GetDodgeForce(), true, false);
	}
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
		if(ItemStructure->Name!="")
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

void AFPS_Character::Scan()
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

bool AFPS_Character::VaultCheck(VaultTraceSettings TraceSettings)
{
	VaultType VaultType;
	FVector InitialTraceImpactPoint;
	FVector InitialTraceNormal;
	FVaultComponentAndTransform TransformAndTransform = FVaultComponentAndTransform();
	float VaultHeight;

	if(FindWallToClimb(TraceSettings, InitialTraceImpactPoint, InitialTraceNormal))
	{
		UE_LOG(LogActor, Error, TEXT("FPS_Character::VaultCheck : Wall founded"));
		if(CanClimbOnWall(TraceSettings, InitialTraceImpactPoint, InitialTraceNormal, VaultHeight, TransformAndTransform, VaultType))
		{
			UE_LOG(LogActor, Error, TEXT("FPS_Character::VaultCheck : Can Climb"));
			VaultStart(VaultHeight, TransformAndTransform, VaultType);
			return true;
		}
	}
	
	return false;
}

void AFPS_Character::VaultStart(float VaultHeight, FVaultComponentAndTransform VaultLedgeWS, VaultType VaultType)
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

bool AFPS_Character::FindWallToClimb(VaultTraceSettings TraceSettings, FVector& InitialTraceImpactPoint, FVector& InitialTraceNormal)
{
	FVector Start = GetCapsuleBaseLocation(2.0f) + GetPlayerInput() * (-30);
	Start.Z += (TraceSettings.MaxLedgeHeight + TraceSettings.MinLedgeHeight) / 2.0f;
	FVector End = Start + GetPlayerInput() * TraceSettings.Distance;
	FHitResult OutHit;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FCollisionShape CapsuleShape = FCollisionShape();
	//CapsuleShape.MakeCapsule(TraceSettings.ForwardTraceRadius, (TraceSettings.MaxLedgeHeight - TraceSettings.MinLedgeHeight) / 2.0f + 1.0f);
	CapsuleShape.MakeCapsule(TraceSettings.ForwardTraceRadius, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	DrawDebugCapsule(GetWorld(), Start, ((TraceSettings.MaxLedgeHeight - TraceSettings.MinLedgeHeight) / 2.0f + 1.0f), TraceSettings.ForwardTraceRadius, FQuat::Identity, FColor::Green, false, 5.0f);
	DrawDebugCapsule(GetWorld(), End, ((TraceSettings.MaxLedgeHeight - TraceSettings.MinLedgeHeight) / 2.0f + 1.0f), TraceSettings.ForwardTraceRadius, FQuat::Identity, FColor::Red, false, 5.0f);
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

bool AFPS_Character::CanClimbOnWall(VaultTraceSettings TraceSettings, FVector& InitialTraceImpactPoint, FVector& InitialTraceNormal, float& VaultHeight, FVaultComponentAndTransform& TransformAndTransform, VaultType& Vault)
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
		UE_LOG(LogActor, Error, TEXT("FPS_Character::CanClimbOnWall : %s"), *OutHit.GetActor()->GetName());
		if (/*GetCharacterMovement()->IsWalkable(OutHit)*/ true)
		{
			UE_LOG(LogActor, Error, TEXT("FPS_Character::CanClimbOnWall : Can Climb"));
			DownTraceLocation = FVector(OutHit.Location.X, OutHit.Location.Y, OutHit.ImpactPoint.Z);
			DrawDebugPoint(GetWorld(), DownTraceLocation, 10.0f, FColor::Yellow, false, 5.0f);
			DrawDebugLine(GetWorld(), DownTraceLocation, DownTraceLocation + FVector(200.0f, 0, 0), FColor::Yellow, false, 5.0f);
			DrawDebugLine(GetWorld(), DownTraceLocation, DownTraceLocation + FVector(0.0f, 0, 200.0f), FColor::Yellow, false, 5.0f);
			if(CapsuleHasRoomCheck(GetCapsuleBaseLocationFromBase(DownTraceLocation, 2.0f), 0.0f, 0.0f))
			{
				FVector toRot = InitialTraceNormal * FVector(-1.0f, -1.0f, 0.0f);
				FTransform Transform = FTransform(toRot.Rotation(), GetCapsuleBaseLocationFromBase(DownTraceLocation, 2.0f), FVector::OneVector);
				TransformAndTransform = FVaultComponentAndTransform(OutHit.GetComponent(), Transform);
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

bool AFPS_Character::CapsuleHasRoomCheck(FVector TargetLocation, float HeightOffset, float RadiusOffset)
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

FVaultComponentAndTransform AFPS_Character::ConvertWorldToLocal(FVaultComponentAndTransform WorldSpaceVault)
{
	FTransform TransformLocal = WorldSpaceVault.Transform * WorldSpaceVault.Component->GetComponentTransform().Inverse();
	return  FVaultComponentAndTransform(WorldSpaceVault.Component, TransformLocal);
}

FVaultComponentAndTransform AFPS_Character::ConvertLocalToWorld(FVaultComponentAndTransform LocalSpaceVault)
{
	FTransform TransformWorld = LocalSpaceVault.Transform * LocalSpaceVault.Component->GetComponentTransform();
	return FVaultComponentAndTransform(LocalSpaceVault.Component, TransformWorld);
}

FVaultParams AFPS_Character::GetVaultParam(VaultType Vault, float VaultHeight)
{
	FVaultAsset VaultAsset;
	switch (Vault)
	{
	case VaultType::LowVault :
		VaultAsset = LowVaultAsset;
		break;
	case VaultType::HighVault :
		VaultAsset = HightVaultAsset;
		break;
	case VaultType::FallingCatch :
		VaultAsset = FallingVaultAsset;
	}

	float PlayRate = UKismetMathLibrary::MapRangeClamped(VaultHeight, VaultAsset.LowHeight, VaultAsset.HightHeight, VaultAsset.LowPlayRate, VaultAsset.HightPlayRate);
	float StartingPos = UKismetMathLibrary::MapRangeClamped(VaultHeight, VaultAsset.LowHeight, VaultAsset.HightHeight, VaultAsset.LowStartPosition, VaultAsset.HightStartPosition);

	return FVaultParams(VaultAsset, PlayRate, StartingPos);
	
}

FTransform AFPS_Character::GetVaultStartOffset(FTransform& VaultTarget)
{
	FTransform OutputTransform;
	OutputTransform.SetLocation(GetActorTransform().GetLocation() - VaultTarget.GetLocation());
	OutputTransform.SetRotation(GetActorTransform().GetRotation() - VaultTarget.GetRotation());
	OutputTransform.SetScale3D(GetActorTransform().GetScale3D() - VaultTarget.GetScale3D());
	return  OutputTransform;
}

FTransform AFPS_Character::GetVaultAnimatedStartOffset(FVaultParams& VaultParam, FTransform& VaultTarget)
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

