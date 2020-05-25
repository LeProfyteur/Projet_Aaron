// Fill out your copyright notice in the Description page of Project Settings.


#include "Flock.h"
#include "Projet_Aaron/Flocking/Rules/BoxAttractionRule.h"
#include "Kismet/KismetMathLibrary.h"

void AFlock::SpawnFlock()
{
	const FRandomStream Random(RandomSeed);
	const FVector Extents = BoundingBox->GetScaledBoxExtent();
	for (int32 Index = 0; Index < AgentCount; Index++)
	{
		const FVector LocalSpawnPosition = FVector(
			Random.FRandRange(-Extents.X, Extents.X),
			Random.FRandRange(-Extents.X, Extents.X),
			Random.FRandRange(-Extents.X, Extents.X)
		);
		const FVector WorldSpawnPosition = GetActorTransform().TransformPosition(LocalSpawnPosition);

		const FVector Velocity = Random.VRand() * MaxAgentVelocity;
		const FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, Velocity);
		const FTransform SpawnTransform(SpawnRotation, WorldSpawnPosition);

		AFlockAgent* Agent = GetWorld()->SpawnActor<AFlockAgent>(AFlockAgent::StaticClass(), SpawnTransform);
		Agent->AgentVelocity = Velocity;
		Agent->Steering = FVector::ZeroVector;

		//Setup mutual reference
		Agent->SetFlock(this);
		Agents.Add(Agent);
	}
}

// Sets default values
AFlock::AFlock()
: MaxSteeringForce(100)
, MaxAgentVelocity(100)
, bEnableSpawnBoxAttraction(true)
, SpawnBoxAttractionMaxForce(10.0)
, RandomSeed(0)
, AgentCount(100)
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BoundingBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoundingBox"));
	BoundingBox->SetupAttachment(RootComponent);
	BoundingBox->SetBoxExtent(FVector(500, 500, 500));
}

float AFlock::GetMaxSteeringForce() const
{
	return MaxSteeringForce;
}

float AFlock::GetMaxAgentVelocity() const
{
	return MaxAgentVelocity;
}

USkeletalMesh* AFlock::GetSkeletalMesh() const
{
	return SkeletalMesh;
}

UAnimationAsset* AFlock::GetAnimationAsset() const
{
	return AnimationAsset;
}

void AFlock::GetFlockingRules(TArray<UFlockingRule*>& OutFlockingRules) const
{
	OutFlockingRules.Empty(FlockingRules.Num());
	for (auto* Rule : FlockingRules)
	{
		OutFlockingRules.Add(Rule);
	}
}

void AFlock::GetFlockAgents(TArray<AFlockAgent*>& OutAgents) const
{
	OutAgents.Empty(Agents.Num());
	for (auto* Agent : Agents)
	{
		OutAgents.Add(Agent);
	}
}

void AFlock::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SpawnFlock();

	if (bEnableSpawnBoxAttraction)
	{
		UBoxAttractionRule* BoxAttractionRule = NewObject<UBoxAttractionRule>();
		BoxAttractionRule->SetBoxComponent(BoundingBox);
		
		FlockingRules.Add(BoxAttractionRule);
	}
}