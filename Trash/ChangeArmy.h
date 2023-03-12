// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/WarbandUnitInfoStruct.h"
#include "Structs/ArmyUnitInfoStruct.h"
#include "Structs/ArmyInfoStruct.h"
#include "ChangeArmy.generated.h"

class	FSQLiteDatabase;
class	FSQLitePreparedStatement;
class	UListView;

/**
 * 
 */
UCLASS()
class FIELDOFBATTLE_API UChangeArmy : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintCallable)
	void GetArmy();

	UFUNCTION(BlueprintImplementableEvent)
	void AddArmyToListview();

	UFUNCTION(BlueprintCallable)
	void GetWarbandUnits(FString InWarband);

	UFUNCTION(BlueprintImplementableEvent)
	void AddWarbandUnitsToListview();

	UFUNCTION(BlueprintCallable)
	void GetArmyUnits(FString InArmyId);

	UFUNCTION(BlueprintImplementableEvent)
	void AddArmyUnitsToListview();

	UFUNCTION(BlueprintCallable)
	void DeleteArmy(FString ArmyId);

	UFUNCTION(BlueprintCallable)
	void DeleteArmyUnits(FString ArmyId);

	UFUNCTION(BlueprintCallable)
	void SaveArmyUnits(FArmyUnitInfoStruct NewArmyUnitInfo, FString NewArmyId);

	UPROPERTY(BlueprintReadWrite)
	FWarbandUnitInfoStruct WarbandUnitInfo;

	UPROPERTY(BlueprintReadWrite)
	FArmyUnitInfoStruct ArmyUnitInfo;

	UPROPERTY(BlueprintReadWrite)
	FArmyInfoStruct ArmyInfo;

private:

	FSQLiteDatabase* FoBDB;
	FString DBPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() + "Database/FoB.db");
	FSQLitePreparedStatement* DeleteArmyStatement;
	FSQLitePreparedStatement* DeleteArmyUnitsStatement;
	FSQLitePreparedStatement* GetArmyNames;
	FSQLitePreparedStatement* GetWarbandTable;
	FSQLitePreparedStatement* GetArmyUnitsTable;
	FSQLitePreparedStatement* InsertInUnitTable;

};
