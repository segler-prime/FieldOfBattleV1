// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/WarbandUnitInfoStruct.h"
#include "Structs/ArmyUnitInfoStruct.h"
#include "Structs/ArmyInfoStruct.h"
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
	void GetWarbandUnits(FString InWarband);

	UFUNCTION(BlueprintImplementableEvent)
	void AddWarbandUnitToListview();	
	
	UFUNCTION(BlueprintCallable)
	void GetArmyHeaders();

	UFUNCTION(BlueprintImplementableEvent)
	void AddArmyHeadersToListview();

	UFUNCTION(BlueprintCallable)
	void GetArmyUnits(FString InArmyId);

	UFUNCTION(BlueprintImplementableEvent)
	void AddArmyUnitToListview();

	// Save Functions

	UFUNCTION(BlueprintCallable)
	int SaveArmyHeader(FString NewArmyName, FString NewWarbandName);

	UFUNCTION(BlueprintCallable)
	void SaveArmyUnits(FArmyUnitInfoStruct NewArmyUnitInfo, FString NewArmyId);

	//Delete Functions
	
	UFUNCTION(BlueprintCallable)
	void DeleteArmy(FString ArmyId);

	UFUNCTION(BlueprintCallable)
	void DeleteArmyUnits(FString ArmyId);

	//Storage Variables

	UPROPERTY(BlueprintReadWrite)
	FWarbandUnitInfoStruct WarbandUnitInfo;

	UPROPERTY(BlueprintReadWrite)
	FArmyUnitInfoStruct ArmyUnitInfo;

	UPROPERTY(BlueprintReadWrite)
	FArmyInfoStruct ArmyInfo;

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
