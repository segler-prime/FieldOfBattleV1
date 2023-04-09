// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FieldOfBattle/BattlePlayerController.h"
#include "TeamMapInfoStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FIELDOFBATTLE_API FTeamMapInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	ABattlePlayerController* BattlePlayerController;

	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;
};
