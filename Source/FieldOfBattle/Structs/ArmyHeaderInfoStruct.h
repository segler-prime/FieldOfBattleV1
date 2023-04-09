// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArmyHeaderInfoStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FIELDOFBATTLE_API FArmyHeaderInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 ArmyID = 0;

	UPROPERTY(BlueprintReadWrite)
	FString ArmyWarband;

	UPROPERTY(BlueprintReadWrite)
	FString ArmyName;

	UPROPERTY(BlueprintReadWrite)
	FString ArmyDescription;	
	
	UPROPERTY(BlueprintReadWrite)
	FString ArmyPoints;

	UPROPERTY(BlueprintReadWrite)
	int32 PlayerID = 0;
};
