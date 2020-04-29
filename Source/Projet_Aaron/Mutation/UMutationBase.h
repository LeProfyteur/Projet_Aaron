// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projet_Aaron/Character/CharacterUtils.h"
#include "UObject/NoExportTypes.h"
#include "UMutationBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UUMutationBase : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UUMutationBase();

	//UUMutationBase(UUMutationBase& Mutation);

	virtual void OnEquip(FCharacterSkills& Skills);
	virtual void OnUnEquip(FCharacterSkills& Skills);
	virtual void ActiveEffect();

private:
	
};
