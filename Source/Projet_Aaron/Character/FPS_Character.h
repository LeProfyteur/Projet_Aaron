// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Camera/CameraComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "StateManager.h"

#include "GameFramework/Character.h"
#include "CoreMinimal.h"
#include "Projet_Aaron/Item/UInventoryCastObject.h"
#include "Projet_Aaron/Item/MainHudFixedSizeCPP.h"
#include "Projet_Aaron/Item/HUDCPP.h"
#include "Projet_Aaron/InventaireComponent.h"
#include "FPS_Character.generated.h"

UCLASS()
class PROJET_AARON_API AFPS_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPS_Character();

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly)
	class UCameraComponent* fpsCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStateManager* stateManager;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UPostProcessComponent* postProcess;
	
	UPROPERTY()
		class AActor* lastActorHit = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isNearClimbing = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* LeftArmEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* RightArmEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UInventaireComponent* InventaireComponent;

	//ANightVisionEquipment *NightVisionEquipment;
	//AGrapnelEquipment* GrapnelEquipment;

	//UPROPERTY(BlueprintReadOnly)
	FHitResult* hitActor = nullptr;
	FHitResult *hitGrab;

	

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAnchors AnchorsCastWidget;*/
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAnchors AnchorsInventoryWindow;*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Alignment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RaycastDistanceInventory = 1000.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		class UUInventoryCastObject* InventoryCastObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMainHudFixedSizeCPP* MainHudFixedSizeCPP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UHUDCPP* HudCPP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUInventoryCastObject> InventoryCastObjectClass;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		TSubclassOf<class UMainHudFixedSizeCPP> MainHudFixedSizeCPPClass;

	bool isSprinting = false;
	bool bPressedAlt = false;
	bool isNightVison = false;
	bool canGrab = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	
	void StartJump();
	
	void Sprint();
	void StopSprint();

	void StartAlt();
	void StopAlt();

	void Crouching();
	void Dodge(FVector direction);
	void Climb(float value);

	void RecoveryStamina(float deltaTime);

	void Action();
	void StopAction();
	void Analyse();

	void ActivatePressedLeft();
	void ActivateReleasedLeft();

	void ActivatePressedRight();
	void ActivateReleasedRight();
	
	void PressedItemWheel();
	void ReleaseItemWheel();

	UFUNCTION(BlueprintCallable)
	void UseMyItem(UDA_SlotStructure* ChosenSlot);
	void PressedUseQuickItem();

	UFUNCTION(BlueprintCallable) void StopClimbing();

};
