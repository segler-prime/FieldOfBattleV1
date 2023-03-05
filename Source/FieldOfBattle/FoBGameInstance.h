// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PlayerInfoStruct.h"
#include "BattleInfoStruct.h"
#include "FoBGameInstance.generated.h"

/**
 * 
 */

UCLASS()
class FIELDOFBATTLE_API UFoBGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	UFoBGameInstance(const FObjectInitializer & ObjectInitializer);

	void Init();

	//Functions to be used by the menu widgets
	void HostSession(FBattleInfoStruct BattleInfo);
	void FindSessions(int32 MaxSearchResults);
	void JoinASession();
	void DestroySession();

	UFUNCTION(BlueprintCallable)
	FBattleInfoStruct GetBattleInfo();
		
	UFUNCTION(BlueprintCallable)
	void SetJoinMenuPtr(UUserWidget* JoinMenuPtr);

	UFUNCTION(BlueprintCallable)
	void SetSelectedSessionIndex(int32 Index, FString BattleName);

	UFUNCTION(BlueprintCallable)
	void SavePlayerInfo(FPlayerInfoStruct InPlayerInfo);

	UFUNCTION(BlueprintCallable)
	FPlayerInfoStruct GetPlayerInfo();

private:

	IOnlineSessionPtr OnlineSessionInterface;
	TSharedPtr<FOnlineSessionSearch> OnlineSessionSearch;
	
	UPROPERTY()
	class UMenu* JoinMenu;
	
	void CreateSession();

	//Online Session Delegate Callbacks
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult);
	void OnDestroySessionComplete(FName Sessionname, bool bWasSuccessful);
	void OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);
		
	//Saved Host Game Conditions
	FBattleInfoStruct BattleInfoSave;
	
	//Saved PlayerInfo
	FPlayerInfoStruct PlayerInfoSave;
	
	//Saved Join Game Conditions
	int32 SelectedSessionIndexSave;
	FString SelectedSessionBattleNameSave = FString::Printf(TEXT("none"));

};
