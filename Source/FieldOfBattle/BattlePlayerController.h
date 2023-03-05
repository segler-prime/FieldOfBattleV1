// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerInfoStruct.h"
#include "BattlePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FIELDOFBATTLE_API ABattlePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void GetPlayerInfo();

protected:

	UPROPERTY(BlueprintReadWrite)
	FPlayerInfoStruct PlayerInfo;
};
