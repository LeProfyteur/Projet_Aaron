#include "FlockAlignmentRule.h"
#include "Projet_Aaron/Flocking/Flock.h"

void UFlockAlignmentRule::Execute_Implementation(UWorld* World, AFlockAgent* Agent)
{
	if (AFlock * Flock = Agent->GetFlock())
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
				//Each visible agent should have the same impact (thus resizing to MaxForce)
				FVector NormalizedVelocity = OtherAgent->GetAgentVelocity();
				NormalizedVelocity.Normalize();
				Force += NormalizedVelocity * MaxForce;
			}
		}
		//Clamping the accumulated Force to MaxForce to mitigate mid-swarm rigidity
		Force = Force.GetClampedToMaxSize(MaxForce);
		
		Agent->AddSteeringForce(Force);
	}
}
