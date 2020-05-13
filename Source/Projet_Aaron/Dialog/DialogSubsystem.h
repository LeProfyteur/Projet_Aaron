// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "Dialog.h"
#include "Containers/Queue.h"

#include "DialogSubsystem.generated.h"

class UAaronSaveGame;
class UDialog;
/**
 * 
 */
UCLASS()
class PROJET_AARON_API UDialogSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "metrics")
	TMap<FString, int32> Metrics;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "metrics")
	TMap<FString, bool> Knowledge;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "metrics")
	TMap<FString, bool> Dialog;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "dialogqueue")
	TQueue<UDialog*> DialogQueue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "dialogqueue")
	bool DialogPlaying;

	UFUNCTION(BlueprintCallable)
	void Clear();
	
	UFUNCTION(BlueprintCallable)
	static void SetMetric(FString MetricToUpdate, int32 NewValue);

	UFUNCTION(BlueprintCallable)
	static void IncrementMetric(FString MetricToUpdate);

	UFUNCTION(BlueprintCallable)
	static void UpdateKnowledge(FString KnowledgeToUpdate);

	UFUNCTION(BlueprintCallable)
	static int GetMetric(FString MetricToGet);

	UFUNCTION(BlueprintCallable)
	static bool GetKnowledge(FString KnowledgeToGet);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void QueueDialog(UObject* WorldContextObject, UDialog* DataAssetDialog);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	void UpdateQueue(UObject* WorldContextObject);

	FTimerHandle TimeHandle;

	UDialog* DialogAsset;
	UObject* World;

	float TimeBetweenDialog = 2.0f;

	void ResetTimer();


};
