// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureStatManager.h"
#include "CharacterStatManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UCharacterStatManager : public UCreatureStatManager
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float DodgeStaminaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float DodgeForce;
};
