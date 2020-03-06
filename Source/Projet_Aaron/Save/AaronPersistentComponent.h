// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AaronPersistentComponent.generated.h"


UCLASS( ClassGroup=(ProjetAaron), meta=(BlueprintSpawnableComponent) )
class PROJET_AARON_API UAaronPersistentComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UAaronPersistentComponent();
};
