// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerState.h"
#include "FoBGameInstance.h"

void ALobbyPlayerState::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("ALobbyPlayerState::BeginPlay - Starting"));

	if (HasLocalNetOwner())
	{
		//UE_LOG(LogTemp, Warning, TEXT("ALobbyPlayerState::BeginPlay - Local"));

		UFoBGameInstance* FoBGameInstance = Cast<UFoBGameInstance>(GetGameInstance());
		FPlayerInfoStruct PlayerInfo = FoBGameInstance->GetPlayerInfo();

		SavePlayerInfo(PlayerInfo);
	}
}