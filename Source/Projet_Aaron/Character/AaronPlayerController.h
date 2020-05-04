// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "AaronPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API AAaronPlayerController : public APlayerController
{
	GENERATED_BODY()

        AAaronPlayerController();

public:

    /** Can be called to check and see if the player is currently using a gamepad */
    UPROPERTY(Transient, BlueprintReadOnly)
        bool bIsUsingGamepad;

    /** Specifies whether we set `bIsUsingGamepad` to `false` if we receive no input for a period of time. If set to 'true', GamepadTimeout will control how long
        we need to go without receiving input before we set `bIsUsingGamepad` to `false`. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        bool bResetGamepadDetectionAfterNoInput;

    /** How long we can go without receiving a gamepad input before we assume they've stopped using the gamepad */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bResetGamepadDetectionAfterNoInput"))
        float GamepadTimeout;


    // Overrides
    virtual bool InputAxis(FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad) override;
    virtual bool InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad) override;
    virtual void PlayerTick(float DeltaTime) override;

protected:

    /** Common logic needed in both `InputAxis()` and `InputKey()` */
    FORCEINLINE void _UpdateGamepad(bool bGamepad)
    {
        bIsUsingGamepad = bGamepad;
        if (bGamepad)
        {
            LastGamepadInputTime = GetWorld()->TimeSeconds;
        }
    }

    // Used to keep track of when we last saw gamepad input
    UPROPERTY(Transient, BlueprintReadOnly)
        float LastGamepadInputTime;
};
