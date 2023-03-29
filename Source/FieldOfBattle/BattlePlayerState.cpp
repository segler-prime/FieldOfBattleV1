// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePlayerState.h"
#include "FoBGameInstance.h"

void ABattlePlayerState::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("ABattlePlayerState::BeginPlay"));

	if (HasLocalNetOwner())
	{
		//UE_LOG(LogTemp, Warning, TEXT("ABattlePlayerState - CLIENT"));

		UFoBGameInstance* FoBGameInstance = Cast<UFoBGameInstance>(GetGameInstance());
		FPlayerInfoStruct PlayerInfo = FoBGameInstance->GetPlayerInfo();

		SavePlayerInfo(PlayerInfo);
	}
}

