// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArmyInfoStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FIELDOFBATTLE_API FArmyInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 ArmyID;

	UPROPERTY(BlueprintReadWrite)
	FString ArmyWarband;

	UPROPERTY(BlueprintReadWrite)
	FString ArmyName;

};
