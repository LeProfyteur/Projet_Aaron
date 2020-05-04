// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMutationBase.h"
#include "AllergyMutation.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API UAllergyMutation : public UUMutationBase
{
	GENERATED_BODY()

public:

	UAllergyMutation();

	virtual void OnEquip(FCharacterSkills& Skills) override;
	virtual void OnUnEquip(FCharacterSkills& Skills) override;
	
};
