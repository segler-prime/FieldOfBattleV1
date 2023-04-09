// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArmyUnitInfoStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FIELDOFBATTLE_API FArmyUnitInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString UnitName;

	UPROPERTY(BlueprintReadWrite)
	FString MoveStat;

	UPROPERTY(BlueprintReadWrite)
	FString FightStat;

	UPROPERTY(BlueprintReadWrite)
	FString ShootStat;

	UPROPERTY(BlueprintReadWrite)
	FString AttacksStat;

	UPROPERTY(BlueprintReadWrite)
	FString ToughnessStat;

	UPROPERTY(BlueprintReadWrite)
	FString WoundsStat;

	UPROPERTY(BlueprintReadWrite)
	FString StrengthStat;

	UPROPERTY(BlueprintReadWrite)
	FString BraveryStat;

	UPROPERTY(BlueprintReadWrite)
	FString InitiativeStat;

	UPROPERTY(BlueprintReadWrite)
	FString UnitStrengthStat;

	UPROPERTY(BlueprintReadWrite)
	int32 BaseCostStat = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 UnitSizeStat = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 ArmyID = 0;

};
