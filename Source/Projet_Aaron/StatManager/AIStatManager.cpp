// Fill out your copyright notice in the Description page of Project Settings.


#include "AIStatManager.h"
#include <Runtime\AIModule\Classes\Perception\AIPerceptionComponent.h>

// Sets default values for this component's properties
UAIStatManager::UAIStatManager() : Super()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAIStatManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIStatManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAIStatManager::SetUpRadiusPerception()
{
	APawn* owner = Cast<APawn>(this->GetOwner());
	AAIController* AiController = Cast<AAIController>(owner->GetController());
    
    FAISenseID Id = UAISense::GetSenseID(UAISense_Sight::StaticClass());

    if (!Id.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Wrong Sense ID"));
        return;
    }

    UAISenseConfig* Config = AiController->GetPerceptionComponent()->GetSenseConfig(Id);

    if (Config == nullptr)
        return;

    UAISenseConfig_Sight* ConfigSight = Cast<UAISenseConfig_Sight>(Config);

    // Save original lose range
    float LoseRange = ConfigSight->LoseSightRadius - ConfigSight->SightRadius;

    ConfigSight->SightRadius = RadiusPercetion;

    // Apply lose range to new radius of the sight
    ConfigSight->LoseSightRadius = ConfigSight->SightRadius + LoseRange;

    AiController->GetPerceptionComponent()->RequestStimuliListenerUpdate();
}

