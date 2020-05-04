// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AaronPersistentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSave);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoad);

struct FActorRecord;

/**
 * This component marks an Actor as Persistent. It will be used to select which actors are persisted.
 * During Loads, every Persistent Actor is wiped from existence to avoid :
 *	- Duplication (A persistent Actor statically placed in the scene that will be copied at load)
 *	- Ghosting (A persistent Actor statically placed in the scene that was destroyed and thus not persisted in the save)
 */
UCLASS( ClassGroup=(ProjetAaron), meta=(BlueprintSpawnableComponent) )
class PROJET_AARON_API UAaronPersistentComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UAaronPersistentComponent();

	UPROPERTY(BlueprintAssignable)
		FOnSave OnSave;

	UPROPERTY(BlueprintAssignable)
		FOnLoad OnLoad;

	/**
	 * Transient Actors are never persisted. Use this to ensure that an Actor is always wiped at each Load but not persisted.
	 */
	UPROPERTY(EditAnywhere)
		bool Transient;

	/**
	 * MAYDO : Add a Transient Component List ?
	 */
};
