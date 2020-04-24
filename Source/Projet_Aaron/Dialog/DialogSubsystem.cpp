// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogSubsystem.h"
#include "Engine/Engine.h"
#include "AIController.h"

void UDialogSubsystem::Clear()
{
	Metrics.Reset();
	Knowledge.Reset();
	Dialog.Reset();

	DialogPlaying = false;

	DialogQueue.Empty();
}

void UDialogSubsystem::SetMetric(FString MetricToUpdate, int32 NewValue)
{
	if(GEngine)
	{
		if( UDialogSubsystem* DialogSubsystem = GEngine->GetEngineSubsystem<UDialogSubsystem>() )
		{
			DialogSubsystem->Metrics.Add(MetricToUpdate, NewValue);
		}
	}
}

void UDialogSubsystem::IncrementMetric(FString MetricToUpdate)
{
	if (GEngine)
	{
		if ( UDialogSubsystem* DialogSubsystem = GEngine->GetEngineSubsystem<UDialogSubsystem>() )
		{
			DialogSubsystem->Metrics.FindOrAdd(MetricToUpdate)++;
		}
	}
}

void UDialogSubsystem::UpdateKnowledge(FString KnowledgeToUpdate)
{
	if (GEngine)
	{
		if ( UDialogSubsystem* DialogSubsystem = GEngine->GetEngineSubsystem<UDialogSubsystem>() )
		{
			DialogSubsystem->Knowledge.Add(KnowledgeToUpdate, true);
		}
	}
}

int UDialogSubsystem::GetMetric(FString MetricToGet)
{
	if (GEngine)
	{
		if ( UDialogSubsystem* DialogSubsystem = GEngine->GetEngineSubsystem<UDialogSubsystem>() )
		{
			if(int32* ptr = DialogSubsystem->Metrics.Find(MetricToGet))
			{
				return *ptr;
			}
		}
	}
	return 0;
}

bool UDialogSubsystem::GetKnowledge(FString KnowledgeToGet)
{
	if (GEngine)
	{
		if ( UDialogSubsystem* DialogSubsystem = GEngine->GetEngineSubsystem<UDialogSubsystem>() )
		{
			if (bool* ptr = DialogSubsystem->Knowledge.Find(KnowledgeToGet))
			{
				return *ptr;
			}
		}
	}
	return false;
}

void PlayDialog(UObject* WorldContextObject, UDialog* DataAssetDialog)
{
	UE_LOG(LogTemp, Warning, TEXT("PlayDialog"));

	if (DataAssetDialog && DataAssetDialog->IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Valide"));
		APawn* Pawn = WorldContextObject->GetWorld()->SpawnActor<APawn>(APawn::StaticClass());
		Pawn->SpawnDefaultController();
		if (AAIController* Controller = Cast<AAIController>(Pawn->GetController()))
		{
			Controller->RunBehaviorTree(DataAssetDialog->DialogBehaviourTree);
			if (UDialogSubsystem* DialogSubsystem = GEngine->GetEngineSubsystem<UDialogSubsystem>())
			{
				DialogSubsystem->DialogPlaying = true;
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Non Valide"));
		if (UDialogSubsystem* DialogSubsystem = GEngine->GetEngineSubsystem<UDialogSubsystem>())
		{
			DialogSubsystem->UpdateQueue(WorldContextObject);
		}
	}
}

void UDialogSubsystem::QueueDialog(UObject* WorldContextObject, UDialog* DataAssetDialog)
{
	UE_LOG(LogTemp, Warning, TEXT("QueueDialog"));
	if (UDialogSubsystem* DialogSubsystem = GEngine->GetEngineSubsystem<UDialogSubsystem>())
	{
		if(DialogSubsystem->DialogPlaying == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("PlayDialoginQueue"));
			PlayDialog(WorldContextObject, DataAssetDialog);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Add to Queue"));
			DialogSubsystem->DialogQueue.Enqueue(DataAssetDialog);
		}
	}
}

void UDialogSubsystem::UpdateQueue(UObject* WorldContextObject)
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateQueue"));

	if (UDialogSubsystem* DialogSubsystem = GEngine->GetEngineSubsystem<UDialogSubsystem>())
	{
		DialogSubsystem->DialogPlaying = false;
		
		if (DialogSubsystem->DialogQueue.IsEmpty() == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("QueuePasVide"));

			DialogSubsystem->DialogQueue.Peek(DialogSubsystem->DialogAsset);
			DialogSubsystem->DialogQueue.Pop();

			DialogSubsystem->World = WorldContextObject;

			WorldContextObject->GetWorld()->GetTimerManager().SetTimer(TimeHandle, this, &UDialogSubsystem::ResetTimer, 2.0f, false);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Vide"));
		}
	}
}

void UDialogSubsystem::ResetTimer()
{
	if (UDialogSubsystem* DialogSubsystem = GEngine->GetEngineSubsystem<UDialogSubsystem>())
	{
		PlayDialog(DialogSubsystem->World, DialogSubsystem->DialogAsset);
	}
}



