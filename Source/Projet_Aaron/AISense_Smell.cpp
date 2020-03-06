// Fill out your copyright notice in the Description page of Project Settings.


#include "AISense_Smell.h"
#include "Projet_Aaron/AISenseConfig_Smell.h"
#include "Projet_Aaron/AISenseEvent_Smell.h"
#include "DrawDebugHelpers.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"


UAISense_Smell::UAISense_Smell()
{
	//Bind the required functions
	OnNewListenerDelegate.BindUObject(this, &UAISense_Smell::OnNewListenerImpl);
	OnListenerRemovedDelegate.BindUObject(this, &UAISense_Smell::OnListenerRemovedImpl);
}

float UAISense_Smell::Update()
{
	AIPerception::FListenerMap& ListenersMap = *GetListeners();

	//For each listener who has this sense we're going to perform a sweep to determine nearby aqua actors
	for (auto& Elem : ListenersMap)
	{
		//Get the listener
		FPerceptionListener Listener = Elem.Value;
		const AActor* ListenerBodyActor = Listener.GetBodyActor();

		for (int32 DigestedPropertyIndex = 0; DigestedPropertyIndex < DigestedProperties.Num(); DigestedPropertyIndex++)
		{
			//Create the sphere for this sense and perform the sweep to determine nearby actors
			FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(DigestedProperties[DigestedPropertyIndex].PhobiaRadius);
			TArray<FHitResult> HitResults;
			GetWorld()->SweepMultiByChannel(HitResults, ListenerBodyActor->GetActorLocation(), ListenerBodyActor->GetActorLocation() + FVector::UpVector * CollisionSphere.GetSphereRadius(), FQuat(), ECollisionChannel::ECC_WorldDynamic, CollisionSphere);

			//Draw debug sphere if we have activated it via the config
			if (DigestedProperties[DigestedPropertyIndex].bDisplayDebugSphere)
			{
				DrawDebugSphere(GetWorld(), ListenerBodyActor->GetActorLocation(), DigestedProperties[DigestedPropertyIndex].PhobiaRadius, 8, FColor::Blue, false, 30.f, 1, 2.f);
			}


			//Check hit results for aqua actors
			for (int32 i = 0; i < HitResults.Num(); i++)
			{
				FHitResult hit = HitResults[i];
				UAIPerceptionStimuliSourceComponent* stimuli = Cast<UAIPerceptionStimuliSourceComponent>(hit.GetActor()->GetComponentByClass(UAIPerceptionStimuliSourceComponent::StaticClass()));
				if (stimuli) {
					UE_LOG(LogTemp, Warning, TEXT("stimuli :"));
					//check if there is the aquaphobia sense in the stimuli
					TArray<TSubclassOf<UAISense>> StimuliSenses = stimuli->RegisterAsSourceForSenses;
					FAISenseID Id = UAISense::GetSenseID(UAISense_Smell::StaticClass());

					if (!Id.IsValid())
					{
						UE_LOG(LogTemp, Error, TEXT("Wrong Sense ID"));
						return 0.f;
					}

					bool isSmellSense = false;
					for (int j = 0; j < StimuliSenses.Num(); j++)
					{
						UE_LOG(LogTemp, Warning, TEXT("Sense Name : %s"), *StimuliSenses[j].Get()->GetName());
						if (StimuliSenses[j].Get()->GetName() == "AISense_Smell")
							isSmellSense = true;
					}

					if (isSmellSense)
					{
						if (FVector::DistSquared(hit.GetActor()->GetActorLocation(), Listener.CachedLocation) <= DigestedProperties[DigestedPropertyIndex].PhobiaRadius * DigestedProperties[DigestedPropertyIndex].PhobiaRadius)
						{
							Elem.Value.RegisterStimulus(hit.GetActor(), FAIStimulus(*this, 1.f, hit.GetActor()->GetActorLocation(), Listener.CachedLocation));
							GLog->Log("registered stimulus!");
						}
						else
						{
							Elem.Value.RegisterStimulus(hit.GetActor(), FAIStimulus(*this, 1.f, hit.GetActor()->GetActorLocation(), Listener.CachedLocation,FAIStimulus::SensingFailed));
						}
					}
				}
			}
		}


	}
	//Time until next update; in this case we're forcing the update to happen in each frame
	return 0.f;
}

void UAISense_Smell::OnNewListenerImpl(const FPerceptionListener& NewListener)
{
	//Since we have at least one AI actor with this sense this function will fire when the game starts
	GLog->Log("hello new listener!");
	check(NewListener.Listener.IsValid());
	//Get the config
	UAISenseConfig* Config = NewListener.Listener->GetSenseConfig(GetSenseID());
	const UAISenseConfig_Smell* SenseConfig = Cast<const UAISenseConfig_Smell>(Config);
	check(SenseConfig);
	//Consume properties from the sense config
	FDigestedAquaProperties PropertyDigest(*SenseConfig);
	DigestedProperties.Add(PropertyDigest);
	RequestImmediateUpdate();
}

void UAISense_Smell::OnListenerRemovedImpl(const FPerceptionListener& UpdatedListener)
{
	//In our case, executes when we stop playing
	GLog->Log("on listener removed!");
}

UAISense_Smell::FDigestedAquaProperties::FDigestedAquaProperties()
{
	//Init.
	PhobiaRadius = 15.f;
	bDisplayDebugSphere = false;
}

UAISense_Smell::FDigestedAquaProperties::FDigestedAquaProperties(const UAISenseConfig_Smell& SenseConfig)
{
	//Copy constructor
	PhobiaRadius = SenseConfig.PhobiaRadius;
	bDisplayDebugSphere = SenseConfig.bDisplayDebugSphere;
}
/*UAIPerceptionStimuliSourceComponent* stimuli = Cast<UAIPerceptionStimuliSourceComponent>(HitResult.GetActor()->GetComponentByClass(UAIPerceptionStimuliSourceComponent::StaticClass()));
if (stimuli) {
	UE_LOG(LogTemp, Warning, TEXT("stimuli :"));
	//check if there is the aquaphobia sense in the stimuli
	/*TArray<TSubclassOf<UAISense>> StimuliSenses = stimuli->RegisterAsSourceForSenses;
	FAISenseID Id = UAISense::GetSenseID(UAISense_Smell::StaticClass());

	if (!Id.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Wrong Sense ID"));
		return 0.f;
	}

	bool isSmellSense = false;
	for (int j = 0; j < StimuliSenses.Num(); j++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sense Name : %s"), *StimuliSenses[j].Get()->GetName());
		if (StimuliSenses[j].Get()->GetName() == "AISense_Smell")
			isSmellSense = true;
	}

	if (isSmellSense)
	{
		if (FVector::DistSquared(HitResult.GetActor()->GetActorLocation(), Listener.CachedLocation) <= Properties.SmellingRange * Properties.SmellingRange)
		{
			Listener.RegisterStimulus(HitResult.GetActor(), FAIStimulus(*this, 1.f, HitResult.GetActor()->GetActorLocation(), Listener.CachedLocation));
			GLog->Log("registered stimulus!");
		}
	}
}*/