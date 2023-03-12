// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Structs/PlayerInfoStruct.h"
#include "LobbyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FIELDOFBATTLE_API ALobbyPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void SavePlayerInfo(FPlayerInfoStruct PlayerInfo);

protected:

};
