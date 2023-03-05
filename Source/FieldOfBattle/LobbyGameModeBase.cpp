// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameModeBase.h"

void ALobbyGameModeBase::PostLogin(APlayerController* InNewPlayer)
{
    Super::PostLogin(InNewPlayer);

    //UE_LOG(LogTemp, Warning, TEXT("ALobbyGameModeBase::PostLogin: Starting"));

    UpdatePlayersList();
 }

void ALobbyGameModeBase::Logout(AController* Existing)
{
    Super::Logout(Existing);
}

void ALobbyGameModeBase::StartGame(FString Map)
{
    //UE_LOG(LogTemp, Warning, TEXT("LobbyGameMode-StartGame: Starting"));
        
    UWorld* World = GetWorld();
    bUseSeamlessTravel = true;
    
    if (Map == "Stoney Bowl")
    {
        World->ServerTravel(TEXT("/Game/Maps/BattleBowlMap?listen"), true);
    }
    
    if (Map == "Scorched Ridge")
    {
        World->ServerTravel(TEXT("/Game/Maps/BattleRidgeMap?listen"), true);
    }

    if (Map == "Grassy Flatland")
    {
        World->ServerTravel(TEXT("/Game/Maps/BattleFlatlandMap?listen"), true);
    }

}

