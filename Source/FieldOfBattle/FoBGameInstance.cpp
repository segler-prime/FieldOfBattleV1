// Fill out your copyright notice in the Description page of Project Settings.


#include "FoBGameInstance.h"
#include "OnlineSubsystem.h"
#include "Session.h"
#include "OnlineSessionSettings.h"

const static FName BATTLE_NAME_KEY = TEXT("CBattleName");
const static FName BATTLE_MAP_KEY = TEXT("CBattleMap");
const static FName BATTLE_TYPE_KEY = TEXT("CBattleType");
const static FName BATTLE_PUBLIC_KEY = TEXT("CBattlePublic");
const static FName BATTLE_PLAYERS_KEY = TEXT("CBattlePlayers");
const static FName BATTLE_TURNS_KEY = TEXT("CBattleTurns");

void UFoBGameInstance::Init()
{
    Super::Init();
    
    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, 
            FString::Printf(TEXT("Found Subsystem: %s"), *OnlineSubsystem->GetSubsystemName().ToString()));
    }

    OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();
    OnlineSessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &ThisClass::OnCreateSessionComplete);
    OnlineSessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &ThisClass::OnFindSessionsComplete);
    OnlineSessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &ThisClass::OnJoinSessionComplete);
    OnlineSessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &ThisClass::OnDestroySessionComplete);

    if (GEngine != nullptr)
    {
        GEngine->OnNetworkFailure().AddUObject(this, &ThisClass::OnNetworkFailure);
    }
}

void UFoBGameInstance::HostSession(FBattleInfoStruct BattleInfo)
{
    //UE_LOG(LogTemp, Warning, TEXT("UFoBGameInstance-HostSession: Starting"));

    if (OnlineSessionInterface.IsValid())
    {
        auto ExistingSession = OnlineSessionInterface->GetNamedSession(NAME_GameSession);
        BattleInfoSave = BattleInfo;
        if (ExistingSession != nullptr)
        {
            DestroySession();
        }
        else
        {
            CreateSession(); 
        }
    }
}

void UFoBGameInstance::CreateSession()
{
    //UE_LOG(LogTemp, Warning, TEXT("UFoBGameInstance-CreateSession: Starting")); 
      
    FOnlineSessionSettings OnlineSessionSettings;
    
    if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
    {
        OnlineSessionSettings.bIsLANMatch = true;
    }
    else
    {
        OnlineSessionSettings.bIsLANMatch = false;
    }

    OnlineSessionSettings.NumPublicConnections = BattleInfoSave.NumPlayers;
    OnlineSessionSettings.bShouldAdvertise = true;
    OnlineSessionSettings.bUsesPresence = true;
    OnlineSessionSettings.bUseLobbiesIfAvailable = true;
    OnlineSessionSettings.bAllowJoinInProgress = true;
    OnlineSessionSettings.bAllowJoinViaPresence = true;

    //Set Battle Info
    OnlineSessionSettings.Set(BATTLE_NAME_KEY, BattleInfoSave.BattleName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
    OnlineSessionSettings.Set(BATTLE_MAP_KEY, BattleInfoSave.Map, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
    OnlineSessionSettings.Set(BATTLE_TYPE_KEY, BattleInfoSave.BattleType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
    OnlineSessionSettings.Set(BATTLE_PUBLIC_KEY, BattleInfoSave.Public, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
    OnlineSessionSettings.Set(BATTLE_PLAYERS_KEY, BattleInfoSave.NumPlayers, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
    OnlineSessionSettings.Set(BATTLE_TURNS_KEY, BattleInfoSave.NumTurns, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

    OnlineSessionInterface->CreateSession(0, NAME_GameSession, OnlineSessionSettings); 
}

void UFoBGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
    //UE_LOG(LogTemp, Warning, TEXT("UFoBGameInstance-OnCreateSessionComplete: Starting"));   
        
    if (!bWasSuccessful)
    {
        UE_LOG(LogTemp, Warning, TEXT("UFoBGameInstance-OnCreateSessionComplete: Session Not Created"));
        return;
    }

    UWorld* World = GetWorld();
    World->ServerTravel("/Game/UI/Lobby/LobbyMap?listen");
}

void UFoBGameInstance::FindSessions(int32 InMaxSearchResults)
{
    //UE_LOG(LogTemp, Warning, TEXT("UFoBGameInstance-FindSessions: Starting"));
    
    OnlineSessionSearch = MakeShareable(new FOnlineSessionSearch());
    
    if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
    {
        OnlineSessionSearch->bIsLanQuery = true;
    }
    else
    {
        OnlineSessionSearch->bIsLanQuery = false;
    }
    
    OnlineSessionSearch->MaxSearchResults = InMaxSearchResults;
    OnlineSessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
    OnlineSessionInterface->FindSessions(0, OnlineSessionSearch.ToSharedRef());
}

void UFoBGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
    //UE_LOG(LogTemp, Warning, TEXT("UFoBGameInstance-OnFindSessionsComplete: Starting"));
    if (bWasSuccessful && OnlineSessionSearch.IsValid())
    {
       JoinMenu->ClearJoinMainTitle();
       int32 SessionIndex = 0;

       for (const FOnlineSessionSearchResult& SearchResult : OnlineSessionSearch->SearchResults)
       {
            //Get Battle Info
            FString BattleNameTemp;
            SearchResult.Session.SessionSettings.Get(BATTLE_NAME_KEY, BattleNameTemp);

            JoinMenu->AddSessionToListview(BattleNameTemp, SearchResult.Session.OwningUserName, SessionIndex);
            SessionIndex = SessionIndex + 1;  
       }
        
        JoinMenu->AddSessionToListview(TEXT("Millys Big Battle"), TEXT("MillyB"), 11);
        JoinMenu->AddSessionToListview(TEXT("Last Man Standing Deathmatch"), TEXT("ToeBasher"), 12);
        JoinMenu->AddSessionToListview(TEXT("For the Queen..."), TEXT("Crumpet"), 13);  
    }
}

void UFoBGameInstance::JoinASession()
{
    //UE_LOG(LogTemp, Warning, TEXT("UFoBGameInstance-JoinASession: Starting")); 

    if (SelectedSessionBattleNameSave == TEXT("none"))
    {
        JoinMenu->SetJoinMainTitle(TEXT("No Battle Selected"));
    }
    else
    {
        if (SelectedSessionIndexSave < 10)
        {
            OnlineSessionSearch->SearchResults[SelectedSessionIndexSave].Session.SessionSettings.Get(BATTLE_NAME_KEY, BattleInfoSave.BattleName);
            OnlineSessionSearch->SearchResults[SelectedSessionIndexSave].Session.SessionSettings.Get(BATTLE_MAP_KEY, BattleInfoSave.Map);
            OnlineSessionSearch->SearchResults[SelectedSessionIndexSave].Session.SessionSettings.Get(BATTLE_TYPE_KEY, BattleInfoSave.BattleType);
            OnlineSessionSearch->SearchResults[SelectedSessionIndexSave].Session.SessionSettings.Get(BATTLE_PUBLIC_KEY, BattleInfoSave.Public);
            OnlineSessionSearch->SearchResults[SelectedSessionIndexSave].Session.SessionSettings.Get(BATTLE_PLAYERS_KEY, BattleInfoSave.NumPlayers);
            OnlineSessionSearch->SearchResults[SelectedSessionIndexSave].Session.SessionSettings.Get(BATTLE_TURNS_KEY, BattleInfoSave.NumTurns);
            OnlineSessionInterface->JoinSession(0, NAME_GameSession, OnlineSessionSearch->SearchResults[SelectedSessionIndexSave]);
        }
    }
}

void UFoBGameInstance::OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type JoinResult)
{
    //UE_LOG(LogTemp, Warning, TEXT("UFoBGameInstance-OnJoinSessionComplete: Starting")); 

    FString Address;
    if (!OnlineSessionInterface->GetResolvedConnectString(InSessionName, Address))
    {
        UE_LOG(LogTemp, Warning, TEXT("UFoBGameInstance-OnJoinSessionComplete: Connect Failed"));
        return; 
    }
    
    APlayerController* PlayerController = GetFirstLocalPlayerController();
    PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
} 

void UFoBGameInstance::DestroySession()
{
    OnlineSessionInterface->DestroySession(NAME_GameSession);
}

void UFoBGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
    //UE_LOG(LogTemp, Warning, TEXT("UFoBGameInstance-OnDestroySessionComplete: Starting")); 
    
    if (bWasSuccessful)
    {
        CreateSession();
    }
}

FBattleInfoStruct UFoBGameInstance::GetBattleInfo()
{
    //UE_LOG(LogTemp, Warning, TEXT("UFoBGameInstance-GetBattleInfo: Starting")); 
    return BattleInfoSave;
}

void UFoBGameInstance::SetJoinMenuPtr(UUserWidget * JoinMenuPtr)
{
    JoinMenu = Cast<USession>(JoinMenuPtr);
}

void UFoBGameInstance::SetSelectedSessionIndex(int32 Index, FString BattleName)
{
    //UE_LOG(LogTemp, Warning, TEXT("UFoBGameInstance-SetSelectedSessionIndex: Starting")); 
    
    SelectedSessionIndexSave = Index;
    SelectedSessionBattleNameSave = BattleName;
    JoinMenu->SetJoinMainTitle(BattleName);
}

void UFoBGameInstance::SavePlayerInfo(FPlayerInfoStruct InPlayerInfo)
{
    PlayerInfoSave = InPlayerInfo;
}

FPlayerInfoStruct UFoBGameInstance::GetPlayerInfo()
{
    return PlayerInfoSave;
}

void UFoBGameInstance::SavePlayersInfo(TArray<FPlayerInfoStruct> InPlayersInfo)
{
    PlayersInfoSave = InPlayersInfo;
}

TArray<FPlayerInfoStruct> UFoBGameInstance::GetPlayersInfo()
{
    return PlayersInfoSave;
}

void UFoBGameInstance::OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
    UE_LOG(LogTemp, Warning, TEXT("UFoBGameInstance::OnNetworkFailure: ALERT ==> Network Error "));
    UE_LOG(LogTemp, Warning, TEXT("Error String = %s"), *ErrorString);

    APlayerController* PlayerController = GetFirstLocalPlayerController();
    PlayerController->ClientTravel("/Game/UI/Maps/MainMenuMap", ETravelType::TRAVEL_Absolute);
}

