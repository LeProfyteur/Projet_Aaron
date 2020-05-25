#include "FlockSeparationRule.h"
#include "Projet_Aaron/Flocking/Flock.h"

void UFlockSeparationRule::Execute_Implementation(UWorld* World, AFlockAgent* Agent)
{
	if (AFlock* Flock = Agent->GetFlock())
	{
		FVector Force = FVector::ZeroVector;

		TArray<AFlockAgent*> Agents;
		Flock->GetFlockAgents(Agents);
		for (auto* OtherAgent : Agents)
		{
			if (OtherAgent == Agent) continue;

			const float DistanceSquared = FVector::DistSquared(Agent->GetActorLocation(), OtherAgent->GetActorLocation());
			if (DistanceSquared < FMath::Square(MaxDistance))
			{
				FVector Direction = Agent->GetActorLocation() - OtherAgent->GetActorLocation();
				Direction.Normalize();

				//Force magnitude is inverse proportional to the Distance ratio
				Direction = Direction * FMath::Lerp(MaxForce, 0.0f, FMath::Sqrt(DistanceSquared) / MaxDistance);
				Force += Direction;
			}
		}
		Force = Force.GetClampedToMaxSize(MaxForce);

		Agent->AddSteeringForce(Force);
	}
}
