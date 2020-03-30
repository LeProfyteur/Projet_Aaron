// Fill out your copyright notice in the Description page of Project Settings.


#include "AaronPlayerControllerCPP.h"
#include "Kismet/GameplayStatics.h"

AAaronPlayerControllerCPP::AAaronPlayerControllerCPP()
{
	
}

void AAaronPlayerControllerCPP::SetMetric(UObject* WorldContextObject, FString MetricToUpdate, int32 NewValue)
{
	AAaronPlayerControllerCPP* PlayerController = Cast<AAaronPlayerControllerCPP>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
	
	if (PlayerController)
	{
		PlayerController->Metrics.Add(MetricToUpdate, NewValue);
	}
}

void AAaronPlayerControllerCPP::IncrementMetric(UObject* WorldContextObject, FString MetricToUpdate)
{
	AAaronPlayerControllerCPP* PlayerController = Cast<AAaronPlayerControllerCPP>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
	if (PlayerController)
	{
		PlayerController->Metrics.FindOrAdd(MetricToUpdate)++;
	}
}

void AAaronPlayerControllerCPP::UpdateKnowledge(UObject* WorldContextObject, FString KnowledgeToUpdate)
{
	AAaronPlayerControllerCPP* PlayerController = Cast<AAaronPlayerControllerCPP>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));

	if (PlayerController)
	{
		PlayerController->Knowledge.Add(KnowledgeToUpdate, true);
	}
}

int AAaronPlayerControllerCPP::GetMetric(UObject* WorldContextObject, FString MetricToGet)
{
	AAaronPlayerControllerCPP* PlayerController = Cast<AAaronPlayerControllerCPP>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));

	if (PlayerController)
	{
		if (PlayerController->Metrics.Find(MetricToGet))
		{
			return PlayerController->Metrics[MetricToGet];
		}
		else
		{
			return 0;
		}
	}
	
	return 0;
}

bool AAaronPlayerControllerCPP::GetKnowledge(UObject* WorldContextObject, FString KnowledgeToGet)
{
	AAaronPlayerControllerCPP* PlayerController = Cast<AAaronPlayerControllerCPP>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));

	if (PlayerController)
	{
		if (PlayerController->Knowledge.Find(KnowledgeToGet))
		{
			return PlayerController->Knowledge[KnowledgeToGet];
		}
		else
		{
			return false;
		}
	}
	return false;
	
}
