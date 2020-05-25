#include "FlockCohesionRule.h"
#include "Projet_Aaron/Flocking/Flock.h"

void UFlockCohesionRule::Execute_Implementation(UWorld* World, AFlockAgent* Agent)
{
	if (AFlock* Flock = Agent->GetFlock())
	{
		FVector Force = FVector::ZeroVector;

		TArray<AFlockAgent*> Agents;
		Flock->GetFlockAgents(Agents);
		for (auto* OtherAgent : Agents)
		{
			//Ignore itself
			if (OtherAgent == Agent) continue;

			const float DistanceSquared = FVector::DistSquared(Agent->GetActorLocation(), OtherAgent->GetActorLocation());
			if (DistanceSquared < FMath::Square(MaxDistance))
			{
				FVector Direction = OtherAgent->GetActorLocation() - Agent->GetActorLocation();
				Direction.Normalize();
				Force += Direction * MaxForce;
			}
		}
		Force = Force.GetClampedToMaxSize(MaxForce);

		Agent->AddSteeringForce(Force);
	}
}
