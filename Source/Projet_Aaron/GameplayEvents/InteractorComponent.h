// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractionBeginEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractionProgressEvent, float, Progress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractionCancelEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractionCompleteEvent);

UCLASS( meta=(BlueprintSpawnableComponent) )
class PROJET_AARON_API UInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractorComponent();

	UFUNCTION(BlueprintCallable)
		void StartInteraction();

	UFUNCTION(BlueprintCallable)
		void StopInteraction();

	UFUNCTION(BlueprintCallable)
		bool IsInteracting();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	UPROPERTY(BlueprintAssignable)
		FInteractionBeginEvent OnInteractionBegin;

	UPROPERTY(BlueprintAssignable)
		FInteractionProgressEvent OnInteractionProgress;

	UPROPERTY(BlueprintAssignable)
		FInteractionCancelEvent OnInteractionCancel;

	UPROPERTY(BlueprintAssignable)
		FInteractionCompleteEvent OnInteractionComplete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InteractionDuration = 0;

private:
	bool Interacting = false;
	float RemainingDuration = 0;
};
