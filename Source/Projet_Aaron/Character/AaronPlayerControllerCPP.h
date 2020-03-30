// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AaronPlayerControllerCPP.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_AARON_API AAaronPlayerControllerCPP : public APlayerController
{
	GENERATED_BODY()

public:
	AAaronPlayerControllerCPP();
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= "metrics")
	TMap<FString, int32> Metrics;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category= "metrics")
	TMap<FString, bool> Knowledge;

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void SetMetric(UObject* WorldContextObject, FString MetricToUpdate,int32 NewValue);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void IncrementMetric(UObject* WorldContextObject, FString MetricToUpdate);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static void UpdateKnowledge(UObject* WorldContextObject, FString KnowledgeToUpdate);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static int GetMetric(UObject* WorldContextObject, FString MetricToGet);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static bool GetKnowledge(UObject* WorldContextObject, FString KnowledgeToGet);

};
