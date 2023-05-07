// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArmyUnitTableStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FIELDOFBATTLE_API FArmyUnitTableStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString UnitName;

	UPROPERTY(BlueprintReadWrite)
	AActor* UnitActorBP;
};
