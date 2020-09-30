// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include <GameFramework/Character.h>
#include <Camera/CameraComponent.h>
#include "../StatManager/CharacterStatManager.h"
#include "AaronCharacter.generated.h"

UCLASS()
class PROJET_AARON_API AAaronCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAaronCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* FpsCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCharacterStatManager* StatManager;
	
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

protected:
	UFUNCTION(BlueprintCallable)
		void MoveForward(float Value);
	UFUNCTION(BlueprintCallable)
		void MoveRight(float Value);
};
