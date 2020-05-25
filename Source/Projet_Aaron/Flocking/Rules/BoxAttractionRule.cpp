#include "BoxAttractionRule.h"

#include "Kismet/KismetMathLibrary.h"
#include "Projet_Aaron/Flocking/Flock.h"

void UBoxAttractionRule::SetBoxComponent(UBoxComponent* InBox)
{
	Box = InBox;
}

UBoxComponent* UBoxAttractionRule::GetBoxComponent() const
{
	return Box;
}

void UBoxAttractionRule::Execute_Implementation(UWorld* World, AFlockAgent* Agent)
{
	FVector BoxLocalAgentPosition = Box->GetOwner()->GetActorTransform().InverseTransformPosition(Agent->GetActorLocation());
	FVector Force = FVector::ZeroVector;
	const FVector Extent = Box->GetScaledBoxExtent();

	if (BoxLocalAgentPosition.X > Extent.X)
	{
		Force.X = -MaxForce;
	}
	else if (BoxLocalAgentPosition.X < -Extent.X)
	{
		Force.X = +MaxForce;
	}

	if (BoxLocalAgentPosition.Y > Extent.Y)
	{
		Force.Y = -MaxForce;
	}
	else if (BoxLocalAgentPosition.Y < -Extent.Y)
	{
		Force.Y = +MaxForce;
	}
	
	if (BoxLocalAgentPosition.Z > Extent.Z)
	{
		Force.Z = -MaxForce;
	}
	else if (BoxLocalAgentPosition.Z < -Extent.Z)
	{
		Force.Z = +MaxForce;
	}

	//Clamp to MaxForce (to limit the impact on multiple axis attraction)
	Force = Force.GetClampedToMaxSize(MaxForce);
	
	Agent->AddSteeringForce(Force);
}