// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleInfoStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FIELDOFBATTLE_API FBattleInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString BattleName;

	UPROPERTY(BlueprintReadWrite)
	FString Map;

	UPROPERTY(BlueprintReadWrite)
	FString BattleType;

	UPROPERTY(BlueprintReadWrite)
	FString Public;
	
	UPROPERTY(BlueprintReadWrite)
	int32 NumPlayers;
	
	UPROPERTY(BlueprintReadWrite)
	int32 NumTurns;

};
