// Fill out your copyright notice in the Description page of Project Settings.


#include "AISense_Smell.h"
#include "Projet_Aaron/AISenseConfig_Smell.h"
#include "Projet_Aaron/AISenseEvent_Smell.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AIPerceptionComponent.h"


//----------------------------------------------------------------------//
// FAISmellEvent
//----------------------------------------------------------------------//

FAISmellEvent::FAISmellEvent()
	: Instigator(nullptr), Intensity(0.0f), Location(FAISystem::InvalidLocation)
{
}

FAISmellEvent::FAISmellEvent(AActor* Instigator, float Intensity, const FVector& Location)
	: Instigator(Instigator), Intensity(Intensity), Location(Location)
{
}

void FAISmellEvent::Compile()
{
	if (!FAISystem::IsValidLocation(Location))
	{
		if (Instigator)
		{
			UE_LOG(LogTemp, Warning, TEXT("Updating Smell Event Location"));
			Location = Instigator->GetActorLocation();
		}
	}
}

//----------------------------------------------------------------------//
// UAISense_Smell::FDigestedSmellProperties
//----------------------------------------------------------------------//

UAISense_Smell::FDigestedSmellProperties::FDigestedSmellProperties()
	: SmellingRange(0.0f)
{
}

UAISense_Smell::FDigestedSmellProperties::FDigestedSmellProperties(const UAISenseConfig_Smell& SenseConfig)
	: SmellingRange(SenseConfig.SmellingRange)
{
}

//----------------------------------------------------------------------//
// UAISense_Smell
//----------------------------------------------------------------------//

UAISense_Smell::UAISense_Smell(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		OnNewListenerDelegate.BindUObject(this, &UAISense_Smell::OnNewListenerImpl);
		OnListenerUpdateDelegate.BindUObject(this, &UAISense_Smell::OnListenerUpdateImpl);
		OnListenerRemovedDelegate.BindUObject(this, &UAISense_Smell::OnListenerRemovedImpl);
	}
}


void UAISense_Smell::RegisterEvent(const FAISmellEvent& Event)
{
	RegisteredEvents.Add(Event);

	RequestImmediateUpdate();
}

void UAISense_Smell::RegisterWrappedEvent(UAISenseEvent& PerceptionEvent)
{
	UAISenseEvent_Smell* SmellEvent = Cast<UAISenseEvent_Smell>(&PerceptionEvent);
	ensure(SmellEvent);
	if (SmellEvent)
	{
		RegisterEvent(SmellEvent->GetSmellEvent());
	}
}

void UAISense_Smell::ReportSmellEvent(UObject* WorldContextObject, AActor* Instigator, float Intensity)
{
	ReportSmellEventAtLocation(WorldContextObject, Instigator, Intensity, Instigator->GetActorLocation());
}

void UAISense_Smell::ReportSmellEventAtLocation(UObject* WorldContextObject, AActor* Instigator, float Intensity, const FVector& Location)
{
	UAIPerceptionSystem* PerceptionSystem = UAIPerceptionSystem::GetCurrent(WorldContextObject);
	if (PerceptionSystem)
	{
		FAISmellEvent Event(Instigator, Intensity, Location);
		PerceptionSystem->OnEvent(Event);
	}
}

float UAISense_Smell::Update()
{
	AIPerception::FListenerMap& ListenersMap = *GetListeners();
	for (auto& Entry : ListenersMap)
	{
		FPerceptionListener& Listener = Entry.Value;

		//Possible sub-frame invalidated Listener
		if (!Listener.HasSense(GetSenseID()))
		{
			continue;
		}

		const FDigestedSmellProperties& Properties = DigestedProperties[Listener.GetListenerID()];

		for (const FAISmellEvent& Event : RegisteredEvents)
		{
			const float Threshold = FVector::DistSquared(Listener.CachedLocation, Event.Location);
			const float Intensity = FMath::Max(0.0f, Event.Intensity);
			const float SmellingRange = FMath::Max(0.0f, Properties.SmellingRange);
			const float Sensibility = FMath::Square(Intensity + SmellingRange);


			UE_LOG(LogTemp, Warning, TEXT("Listener : %d"), long(Listener.GetListenerID()));
			UE_LOG(LogTemp, Warning, TEXT("Threshold (%s, %s) : %f"), *Listener.CachedLocation.ToString(), *Event.Location.ToString(), Threshold);
			UE_LOG(LogTemp, Warning, TEXT("Intensity : %f"), Intensity);
			UE_LOG(LogTemp, Warning, TEXT("SmellingRange : %f"), SmellingRange);
			UE_LOG(LogTemp, Warning, TEXT("Sensibility : %f"), Sensibility);

			//Threshold is the minimum amount of sensibility a Listener must have to register the event
			if (Sensibility < Threshold)
			{
				continue;
			}

			UE_LOG(LogTemp, Warning, TEXT("Dispatching Smell Event"));
			
			Listener.RegisterStimulus(Event.Instigator, FAIStimulus(*this, Event.Intensity, Event.Location, Listener.GetBodyActor()->GetActorLocation()));
		}
	}

	RegisteredEvents.Reset();
	
	return SuspendNextUpdate;
}

void UAISense_Smell::OnNewListenerImpl(const FPerceptionListener& NewListener)
{
	UAIPerceptionComponent* PerceptionComponent = NewListener.Listener.Get();
	check(PerceptionComponent);
	const UAISenseConfig_Smell* SenseConfig = Cast<const UAISenseConfig_Smell>(PerceptionComponent->GetSenseConfig(GetSenseID()));
	check(SenseConfig);
	const FDigestedSmellProperties PropertyDigest(*SenseConfig);
	DigestedProperties.Add(NewListener.GetListenerID(), PropertyDigest);
}

void UAISense_Smell::OnListenerUpdateImpl(const FPerceptionListener& UpdatedListener)
{
	if (UpdatedListener.HasSense(GetSenseID()))
	{
		const UAISenseConfig_Smell* SenseConfig = Cast<const UAISenseConfig_Smell>(UpdatedListener.Listener->GetSenseConfig(GetSenseID()));
		check(SenseConfig);
		FDigestedSmellProperties& PropertiesDigest = DigestedProperties.FindOrAdd(UpdatedListener.GetListenerID());
		PropertiesDigest = FDigestedSmellProperties(*SenseConfig);
	}
	else
	{
		DigestedProperties.Remove(UpdatedListener.GetListenerID());
	}
}

void UAISense_Smell::OnListenerRemovedImpl(const FPerceptionListener& UpdatedListener)
{
	DigestedProperties.Remove(UpdatedListener.GetListenerID());
}