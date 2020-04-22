// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerAdvancement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJET_AARON_API UPlayerAdvancement : public UActorComponent
{
	GENERATED_BODY()

	TMap <FString, bool> scannableItems = { {"LightPlant",false}, {"PoisonPlant",false} ,{"BlockingPlant",false} ,{"Creature1",false} ,{"Creature2",false} ,{"Creature3",false} ,{"Creature4",false} };
	TMap <FString, bool> unlockableAbilities = { {"LightPlant",false}, {"PoisonPlant",false} ,{"BlockPlant",false} ,{"Creature1",false} ,{"Creature2",false} ,{"Creature3",false} ,{"Creature4",false} };
	TMap <FString, bool> metroidvaniaAbilities{ {"NightVision",false}, {"PoisonPlant",false} ,{"BlockPlant",false} ,{"Creature1",false} ,{"Creature2",false} ,{"Creature3",false} ,{"Creature4",false} };;


public:	
	// Sets default values for this component's properties
	UPlayerAdvancement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
		void SetScannableItemStatus(FString entryName, bool isScanned) { scannableItems[entryName] = isScanned; UE_LOG(LogActor, Error, TEXT("Scan successful"));}

public:
	UFUNCTION(BlueprintCallable)
	bool GetScannableItemStatus(FString entryName) {return scannableItems[entryName];}
		
};
