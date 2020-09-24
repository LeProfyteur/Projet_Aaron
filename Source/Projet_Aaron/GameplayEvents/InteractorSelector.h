// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractorComponent.h"
#include "InteractorSelector.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractorSelectedEvent, UInteractorComponent*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractorDeselectedEvent, UInteractorComponent*, Interactor);

UCLASS(meta=(BlueprintSpawnableComponent) )
class PROJET_AARON_API UInteractorSelector : public USceneComponent
{
	GENERATED_BODY()

public:
	UInteractorSelector();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void StartInteraction();

	UFUNCTION(BlueprintCallable)
		void StopInteraction();

	UFUNCTION(BlueprintCallable)
		bool IsInteracting();

	UFUNCTION(BlueprintCallable)
		UInteractorComponent* GetSelectedInteractor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Range = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UArrowComponent* DebugArrow;

	UPROPERTY(BlueprintAssignable)
		FOnInteractorSelectedEvent OnInteractorSelected;

	UPROPERTY(BlueprintAssignable)
		FOnInteractorDeselectedEvent OnInteractorDeselected;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UInteractorComponent> InteractorTypeFilter = UInteractorComponent::StaticClass();

private:
	void UpdateSelection(UInteractorComponent* NewSelection);
	UInteractorComponent* SelectedInteractor;
};
