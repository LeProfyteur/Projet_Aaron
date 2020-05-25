// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimationAsset.h"
#include "Components/BoxComponent.h"
#include "Engine/SkeletalMesh.h"
#include "GameFramework/Actor.h"
#include "Projet_Aaron/Flocking/FlockingRule.h"
#include "Projet_Aaron/Flocking/FlockAgent.h"
#include "Flock.generated.h"

UCLASS()
class PROJET_AARON_API AFlock : public AActor
{
	GENERATED_BODY()

	/* Flock Data */
protected:
	UPROPERTY(EditAnywhere, Category = "Flocking | Rules", BlueprintGetter = GetMaxSteeringForce)
		float MaxSteeringForce;

	UPROPERTY(EditAnywhere, Category = "Flocking | Rules", BlueprintGetter = GetMaxAgentVelocity)
		float MaxAgentVelocity;

	UPROPERTY(EditAnywhere, Category = "Flocking | Rules")
		bool bEnableSpawnBoxAttraction;

	UPROPERTY(EditAnywhere, Category = "Flocking | Rules")
		float SpawnBoxAttractionMaxForce;


	UPROPERTY(EditAnywhere, Category = "Flocking | Rules", Instanced)
		TArray<UFlockingRule*> FlockingRules;

	UPROPERTY(EditAnywhere, Category = "Flocking | Spawn")
		int32 RandomSeed;

	UPROPERTY(EditAnywhere, Category = "Flocking | Spawn")
		int32 AgentCount;

	UPROPERTY(EditAnywhere, Category = "Flocking | Assets", BlueprintGetter = GetSkeletalMesh)
		USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "Flocking | Assets", BlueprintGetter = GetAnimationAsset)
		UAnimationAsset* AnimationAsset;

	UPROPERTY()
		TArray<AFlockAgent*> Agents;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* BoundingBox;


	void SpawnFlock();

public:	
	AFlock();

	UFUNCTION(BlueprintGetter)
		float GetMaxSteeringForce() const;

	UFUNCTION(BlueprintGetter)
		float GetMaxAgentVelocity() const;

	UFUNCTION(BlueprintGetter)
		USkeletalMesh* GetSkeletalMesh() const;

	UFUNCTION(BlueprintGetter)
		UAnimationAsset* GetAnimationAsset() const;

	UFUNCTION(BlueprintCallable)
		void GetFlockingRules(TArray<UFlockingRule*>& OutFlockingRules) const;

	UFUNCTION(BlueprintCallable)
		void GetFlockAgents(TArray<AFlockAgent*>& OutAgents) const;
protected:
	void PostInitializeComponents() override;
};
