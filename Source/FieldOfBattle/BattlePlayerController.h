// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Structs/PlayerInfoStruct.h"
#include "BattlePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FIELDOFBATTLE_API ABattlePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

protected:

	UPROPERTY(BlueprintReadWrite)
	FPlayerInfoStruct PlayerInfo;
};
