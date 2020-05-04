// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include <UMG.h>
#include "UIManagerSubsystem.generated.h"

UCLASS()
class PROJET_AARON_API UUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	TArray<UUserWidget*> MenuStack;

public:

	UFUNCTION(BlueprintCallable)
		void Initialize();

	UFUNCTION(BlueprintCallable)
		void PopAllMenus();

	UFUNCTION(BlueprintCallable)
		void Reset();

	UFUNCTION(BlueprintCallable)
		void PushMenu(UUserWidget* Menu);

	UFUNCTION(BlueprintCallable)
		void PopMenu();

	UFUNCTION(BlueprintCallable)
		UUserWidget* GetCurrentMenu() const;

	UFUNCTION(BlueprintCallable)
		bool IsShowingAMenu() const;
};