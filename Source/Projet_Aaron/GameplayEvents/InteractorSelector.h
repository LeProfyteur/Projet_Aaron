// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractorSelector.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorSelectedEvent, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorDeselectedEvent, AActor*, Actor);

UCLASS( meta=(BlueprintSpawnableComponent) )
class PROJET_AARON_API UInteractorSelector : public USceneComponent
{
	GENERATED_BODY()

public:	
	UInteractorSelector();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void TryInteracting();

	UFUNCTION(BlueprintCallable)
		void StopInteracting();

	UFUNCTION(BlueprintCallable)
		class AActor* GetSelectedActor();

	UFUNCTION(BlueprintCallable)
		class UInteractorComponent* GetInteractor();

	UFUNCTION(BlueprintCallable)
		bool HasSelection() { return SelectedActor != nullptr; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Range = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UArrowComponent* DebugArrow;

	UPROPERTY(BlueprintAssignable)
		FOnActorSelectedEvent OnActorSelected;

	UPROPERTY(BlueprintAssignable)
		FOnActorDeselectedEvent OnActorDeselected;

private:
	void UpdateSelectedActor(class AActor* Actor);

	bool InteractingWithSelection = false;
	class AActor* SelectedActor;
};
