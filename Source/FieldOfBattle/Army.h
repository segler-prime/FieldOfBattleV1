// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/WarbandUnitInfoStruct.h"
#include "Structs/ArmyUnitInfoStruct.h"
#include "Structs/ArmyHeaderInfoStruct.h"
#include "Army.generated.h"

class FSQLiteDatabase;
class FSQLitePreparedStatement;

/**
 * 
 */
UCLASS()
class FIELDOFBATTLE_API UArmy : public UUserWidget
{
	GENERATED_BODY()

protected:

	//Get Functions

	UFUNCTION(BlueprintCallable)
	TArray<FWarbandUnitInfoStruct> GetWarbandUnits(FString InWarband);

	UFUNCTION(BlueprintCallable)
	TArray<FArmyHeaderInfoStruct> GetArmyHeaders();

	UFUNCTION(BlueprintCallable)
	TArray<FArmyUnitInfoStruct> GetArmyUnits(FString InArmyID);

	// Save Functions

	UFUNCTION(BlueprintCallable)
	int SaveArmyHeader(FArmyHeaderInfoStruct NewArmyHeaderInfo);

	UFUNCTION(BlueprintCallable)
	void SaveArmyUnits(FArmyUnitInfoStruct NewArmyUnitInfo, FString NewArmyID);

	//Delete Functions
	
	UFUNCTION(BlueprintCallable)
	void DeleteArmy(FString ArmyID);

	UFUNCTION(BlueprintCallable)
	void DeleteArmyUnits(FString ArmyID);

private:

	FSQLiteDatabase * FoBDB;
	FString DBPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() + "Database/FoB.db");
	
	FSQLitePreparedStatement* WarbandUnitTable;
	FSQLitePreparedStatement* ArmyHeadersTable;
	FSQLitePreparedStatement* ArmyUnitsTable;
	FSQLitePreparedStatement* GetNewArmyId;
	
	FSQLitePreparedStatement* InsertInArmyHeaderTable;
	FSQLitePreparedStatement* InsertInArmyUnitTable;

	FSQLitePreparedStatement* DeleteArmyHeaderStmt;
	FSQLitePreparedStatement* DeleteArmyUnitsStmt;
};
