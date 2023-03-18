// Fill out your copyright notice in the Description page of Project Settings.

#include "Session.h"
#include "FoBGameInstance.h"
#include "LobbyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
       
    void USession::HostButtonClicked(FBattleInfoStruct BattleInfo)
    {
        //UE_LOG(LogTemp, Warning, TEXT("USession::HostButtonClicked: Starting"));

        FoBGameInstancePtr = Cast<UFoBGameInstance>(GetGameInstance());
        FoBGameInstancePtr->HostSession(BattleInfo);
    }

    void USession::StartButtonClicked(FString Map)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Menu-StartButtonClicked: Starting"));
        ALobbyGameModeBase* LobbyGameMode = Cast<ALobbyGameModeBase>(UGameplayStatics::GetGameMode(this));  
        LobbyGameMode->StartGame(Map);
    }

    void USession::JoinButtonClicked()
    {               
        //UE_LOG(LogTemp, Warning, TEXT("Menu-JoinButtonClicked: Starting"));
        FoBGameInstancePtr = Cast<UFoBGameInstance>(GetGameInstance());
        FoBGameInstancePtr->JoinASession();
    }

	void USession::FindSessions()
    {
        //UE_LOG(LogTemp, Warning, TEXT("Menu-FindSessions: Starting"));
        FoBGameInstancePtr = Cast<UFoBGameInstance>(GetGameInstance()); 
        FoBGameInstancePtr->FindSessions(100);
    }


    


    
