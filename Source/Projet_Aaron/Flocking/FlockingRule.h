#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Projet_Aaron/Flocking/FlockAgent.h"
#include "FlockingRule.generated.h"

UCLASS(Blueprintable, BlueprintType, Abstract, EditInlineNew)
class PROJET_AARON_API UFlockingRule : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintNativeEvent)
		void Execute(UWorld* World, AFlockAgent* Agent);
		virtual void Execute_Implementation(UWorld* World, AFlockAgent* Agent);

	//UGameplayStatics is unreachable so we need to export functions from it manually
	UFUNCTION(BlueprintCallable)
		static APlayerController* GetPlayerController(UWorld* World, int32 PlayerIndex);
	UFUNCTION(BlueprintCallable)
		static APawn* GetPlayerPawn(UWorld* World, int32 Index);
};
