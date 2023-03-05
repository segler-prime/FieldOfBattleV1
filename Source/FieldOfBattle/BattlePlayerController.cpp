// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePlayerController.h"
#include "FoBGameInstance.h"


void ABattlePlayerController::GetPlayerInfo()
{
	UFoBGameInstance* FoBGameInstance = Cast<UFoBGameInstance>(GetGameInstance());
	PlayerInfo = FoBGameInstance->GetPlayerInfo();

}