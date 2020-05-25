#include "CollisionAvoidanceRule.h"
#include "Engine/World.h"

void UCollisionAvoidanceRule::Execute_Implementation(UWorld* World, AFlockAgent* Agent)
{
	FVector ForwardVector = Agent->GetActorForwardVector();
	FVector Start = Agent->GetActorLocation();
	FVector End = Start + ForwardVector * MaxDistance;

	FHitResult Hit;
	if (World->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility))
	{
		//The lesser the HitDistance, the higher the Intensity. DesiredIntensity is a mutliplier (percentage) for the MaxForce
		const float DesiredIntensity = 1.0f - (Hit.Distance / MaxDistance);

		//Aim for the Normal of the Impact (not perfect but should be Okay for simple geometry)
		Agent->AddSteeringForce(Hit.Normal * MaxForce * DesiredIntensity);
	}
}
