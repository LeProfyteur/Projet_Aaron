// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AISense.h"
#include "AISense_Smell.generated.h"

class UAISenseConfig_Smell; // Forward class declaration (Cyclic dependency)

USTRUCT(BlueprintType)
struct PROJET_AARON_API FAISmellEvent
{
	GENERATED_BODY()

	//Template requirement (PerceptionSystem)
	typedef  class UAISense_Smell FSenseClass;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	AActor* Instigator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	float Intensity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	FVector Location;

	FAISmellEvent();
	FAISmellEvent(AActor* Instigator, float Intensity, const FVector& Location);

	void Compile();
};

UCLASS(ClassGroup=AI, Config=Game)
class PROJET_AARON_API UAISense_Smell : public UAISense
{
	GENERATED_BODY()

	struct FDigestedSmellProperties
	{
		float SmellingRange;

		FDigestedSmellProperties();
		FDigestedSmellProperties(const UAISenseConfig_Smell& SenseConfig);
	};
	TMap<FPerceptionListenerID, FDigestedSmellProperties> DigestedProperties;

	
	TArray<FAISmellEvent> RegisteredEvents;

public:
	UAISense_Smell(const FObjectInitializer& ObjectInitializer);
	
	void RegisterEvent(const FAISmellEvent& Event);
	void RegisterWrappedEvent(UAISenseEvent& PerceptionEvent) override;

	UFUNCTION(BlueprintCallable, Category = "AI|Perception", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "Instigator"))
	static void ReportSmellEvent(UObject* WorldContextObject, AActor* Instigator, float Intensity);

	UFUNCTION(BlueprintCallable, Category = "AI|Perception", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "Instigator"))
	static void ReportSmellEventAtLocation(UObject* WorldContextObject, AActor* Instigator, float Intensity, const FVector& Location);

protected:
	float Update() override;
	
	void OnNewListenerImpl(const FPerceptionListener& NewListener);
	void OnListenerUpdateImpl(const FPerceptionListener& UpdatedListener);
	void OnListenerRemovedImpl(const FPerceptionListener& UpdatedListener);
};