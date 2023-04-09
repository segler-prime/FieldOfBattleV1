// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleStatusBarInfoStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FIELDOFBATTLE_API FBattleStatusBarInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 TurnNumber = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 TeamNumber = 0;

	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite)
	FString TurnPhase;
};
