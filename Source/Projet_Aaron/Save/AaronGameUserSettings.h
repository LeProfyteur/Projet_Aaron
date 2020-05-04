// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "AaronGameUserSettings.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,config = GameUserSettings)
class PROJET_AARON_API UAaronGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable)
        float GetMasterSoundVolume();
    UFUNCTION(BlueprintCallable)
        void SetMasterSoundVolume(float Volume);

	UFUNCTION(BlueprintCallable)
    float GetSFXSoundVolume();
	UFUNCTION(BlueprintCallable)
    void SetSFXSoundVolume(float Volume);

    UFUNCTION(BlueprintCallable)
        float GetVoiceSoundVolume();
    UFUNCTION(BlueprintCallable)
        void SetVoiceSoundVolume(float Volume);

    UFUNCTION(BlueprintCallable)
        float GetMusicSoundVolume();
    UFUNCTION(BlueprintCallable)
        void SetMusicSoundVolume(float Volume);

    UFUNCTION(BlueprintCallable)
        float GetMouseSensivity();
    UFUNCTION(BlueprintCallable)
        void SetMouseSensivity(float NewSensivity);

    UFUNCTION(BlueprintCallable)
        bool GetIsToggleSprint();
    UFUNCTION(BlueprintCallable)
        void SetIsToggleSprint(bool IsToggle);

    UFUNCTION(BlueprintCallable)
        int GetHoldingTimeWheel();
    UFUNCTION(BlueprintCallable)
        float GetHoldingTimeWheelSec();
    UFUNCTION(BlueprintCallable)
        void SetHoldingTimeWheel(int HoldingTime);

    // Wipes serialized data if version is invalid
	bool IsVersionValid() override;
	void UpdateVersion() override;

protected:
    //Scale on [0,1]
    UPROPERTY(config)
        float MasterSoundVolume = 1.0f;
	//Scale on [0,1]
    UPROPERTY(config)
        float SFXSoundVolume = 1.0f;
    //Scale on [0,1]
    UPROPERTY(config)
        float MusicSoundVolume = 1.0f;
    //Scale on [0,1]
    UPROPERTY(config)
        float VoiceSoundVolume = 1.0f;

    //Scale on [0.01,5]
    UPROPERTY(config)
        float MouseSensivity = 1.0f;

    UPROPERTY(config)
        bool IsToggleSprint = false;

    UPROPERTY(config)
        int HoldingTimeWheel = 200;
	
};
