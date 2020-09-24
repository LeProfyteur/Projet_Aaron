// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractionBeginEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractionProgressEvent, float, Progress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractionCancelEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractionCompleteEvent);

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent) )
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

	UFUNCTION(BlueprintGetter)
		virtual bool CanInteract();

	UFUNCTION(BlueprintSetter)
		virtual void SetInteractive(bool Interactive);

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
		float InteractionDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText InteractionHint;

	UPROPERTY(EditAnywhere, BlueprintGetter = CanInteract, BlueprintSetter = SetInteractive)
		bool bInteractive = true;

private:
	bool Interacting = false;
	float RemainingDuration = 0;
};