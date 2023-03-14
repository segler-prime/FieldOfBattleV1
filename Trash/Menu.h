// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FoBGameInstance.h"
#include "Structs/BattleInfoStruct.h"
#include "Menu.generated.h"


/**
 * 
 */

UCLASS()
class FIELDOFBATTLE_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void HostButtonClicked(FBattleInfoStruct BattleInfo);

	UFUNCTION(BlueprintCallable)
	void StartButtonClicked(FString Map);

	UFUNCTION(BlueprintCallable)
	void JoinButtonClicked();

	UFUNCTION(BlueprintCallable)
	void FindSessions();

	UFUNCTION(BlueprintImplementableEvent)
	void AddSessionToListview(const FString& SessionBattleName, const FString& SessionHostName, const int32 SessionIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void ClearListview();

	UFUNCTION(BlueprintImplementableEvent)
	void SetJoinMainTitle(const FString& TitleText);

	UFUNCTION(BlueprintImplementableEvent)
	void ClearJoinMainTitle();

private:
	
	//Pointer to the FOB Game Instance
	class UFoBGameInstance * FoBGameInstancePtr;	

};
