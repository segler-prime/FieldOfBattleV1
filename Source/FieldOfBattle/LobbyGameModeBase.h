// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerInfoStruct.h"
#include "LobbyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FIELDOFBATTLE_API ALobbyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	void StartGame(FString Map);
		
	void PostLogin(APlayerController* NewPlayer) override;

	void Logout(AController* Existing) override; 

	UFUNCTION(BlueprintImplementableEvent)
	void UpdatePlayersList();
	
protected:
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FPlayerInfoStruct> PlayersInfo;

};
