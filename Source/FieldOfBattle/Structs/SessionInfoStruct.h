// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SessionInfoStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FIELDOFBATTLE_API FSessionInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString SessionBattleName;

	UPROPERTY(BlueprintReadWrite)
	FString SessionHostName;

	UPROPERTY(BlueprintReadWrite)
	int32 SessionIndex;
};
