// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArmyHeaderInfoStruct.h"
#include "PlayerInfoStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FIELDOFBATTLE_API FPlayerInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite)
	FArmyHeaderInfoStruct ArmyHeaderInfo;
	
	UPROPERTY(BlueprintReadWrite)
	int32 Team = 0;
};
