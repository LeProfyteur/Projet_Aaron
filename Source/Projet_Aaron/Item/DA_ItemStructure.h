// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "DA_ItemStructure.generated.h"

UENUM(BlueprintType)
enum ECategoryEnum
{
	CE_Consomable UMETA(DisplayName="Consomable"),
	CE_Lore UMETA(DisplayName = "Item de Lore"),
	CE_Seringue UMETA(DisplayName = "Seringue"),
	CE_Tool UMETA(DisplayName = "Tool"),
	CE_Exploration UMETA(DisplayName = "Exploration"),
};

class AItem;

UCLASS(BlueprintType)
class PROJET_AARON_API UDA_ItemStructure : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsConsomable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AItem> Class;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		TEnumAsByte<ECategoryEnum> Category;
	
};
