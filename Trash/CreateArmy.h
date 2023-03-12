// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/WarbandUnitInfoStruct.h"
#include "Structs/ArmyUnitInfoStruct.h"
#include "CreateArmy.generated.h"

class	FSQLiteDatabase;
class	FSQLitePreparedStatement;

/**
 * 
 */
UCLASS()
class FIELDOFBATTLE_API UCreateArmy : public UUserWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable)
	int SaveArmyHeader(FString ArmyName, FString WarbandName);

	UFUNCTION(BlueprintCallable)
	void SaveArmyUnits(FArmyUnitInfoStruct ArmyUnitInfo, FString ArmyId);

	UFUNCTION(BlueprintCallable)
	void GetWarbandUnits(FString InWarband);

	UFUNCTION(BlueprintImplementableEvent)
	void AddAvailableUnitsToListview();

	UPROPERTY(BlueprintReadWrite)
	FWarbandUnitInfoStruct WarbandUnitInfo;

private:

	FSQLiteDatabase * FoBDB;
	FString DBPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() + "Database/FoB.db");
	FSQLitePreparedStatement * InsertInArmyTable;
	FSQLitePreparedStatement * InsertInUnitTable;
	FSQLitePreparedStatement * GetWarbandTable;
	FSQLitePreparedStatement * GetNewArmyId;

};
