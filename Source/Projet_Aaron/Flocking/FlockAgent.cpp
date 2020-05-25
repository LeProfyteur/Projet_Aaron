#include "FlockAgent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Projet_Aaron/Flocking/Flock.h"
#include "Components/SkeletalMeshComponent.h"

AFlockAgent::AFlockAgent()
: Flock(nullptr)
, AgentVelocity(FVector::ZeroVector)
, Steering(FVector::ZeroVector)
{
	PrimaryActorTick.bCanEverTick = true;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = SkeletalMeshComponent;
}

void AFlockAgent::SetFlock(AFlock* InFlock)
{
	//Will only accept if not owned
	if (Flock == nullptr)
	{
		Flock = InFlock;
		SkeletalMeshComponent->SetSkeletalMesh(Flock->GetSkeletalMesh());
		SkeletalMeshComponent->PlayAnimation(Flock->GetAnimationAsset(), true);
	}
}

AFlock* AFlockAgent::GetFlock() const
{
	return Flock;
}

FVector AFlockAgent::GetAgentVelocity() const
{
	return AgentVelocity;
}

FVector AFlockAgent::GetSteering() const
{
	return Steering;
}

void AFlockAgent::AddSteeringForce(const FVector& Force)
{
	Steering += Force;
}

void AFlockAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Flock)
	{
		//Execute every FlockingRule for that Agent
		TArray<UFlockingRule*> FlockingRules;
		Flock->GetFlockingRules(FlockingRules);
		for (auto* Rule : FlockingRules)
		{
			Rule->Execute(GetWorld(), this);
		}

		//Limit Steering force & Apply to Velocity
		Steering = Steering.GetClampedToMaxSize(Flock->GetMaxSteeringForce());
		AgentVelocity += Steering * DeltaTime;

		//Limit Velocity & Apply to Actor Location
		AgentVelocity = AgentVelocity.GetClampedToMaxSize(Flock->GetMaxAgentVelocity());
		SetActorLocation(GetActorLocation() + AgentVelocity * DeltaTime);

		//Update the Orientation according to Velocity (avoid ZeroVector)
		if (!AgentVelocity.IsNearlyZero())
		{
			SetActorRotation(UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, AgentVelocity));
		}
	}
}