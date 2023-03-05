// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	
private:

	FSQLiteDatabase * FoBDB;
	FString DBPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() + "Database/FoB.db");
	FSQLitePreparedStatement * DeleteArmyStatement;
	FSQLitePreparedStatement * DeleteArmyUnitsStatement;
	FSQLitePreparedStatement * GetArmyNames;
	FSQLitePreparedStatement * GetWarbandTable;
	FSQLitePreparedStatement * GetArmyUnitsTable;
	FSQLitePreparedStatement * InsertInUnitTable;

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
	void SaveArmyUnits(FString UnitName, 
					   FString MoveStat, 
					   FString FightStat, 
					   FString ShootStat, 
					   FString StrengthStat, 
					   FString ToughnessStat, 
					   FString WoundsStat, 
					   FString InitiativeStat, 
					   FString AttacksStat, 
					   FString LeadershipStat, 
					   FString UnitStrengthStat, 
					   FString BaseCostStat, 
					   FString UnitSizeStat, 
					   FString ArmyId);

	UPROPERTY(BlueprintReadWrite)
	FString ArmyNameTemp;

	UPROPERTY(BlueprintReadWrite)
	FString WarbandTemp;

	UPROPERTY(BlueprintReadWrite)
	FString ArmyIdTemp;

	UPROPERTY(BlueprintReadWrite)
	FString UnitNameTemp;

	UPROPERTY(BlueprintReadWrite)
	FString MoveStatTemp;

	UPROPERTY(BlueprintReadWrite)
	FString FightStatTemp;

	UPROPERTY(BlueprintReadWrite)
	FString ShootStatTemp;

	UPROPERTY(BlueprintReadWrite)
	FString StrengthStatTemp;

	UPROPERTY(BlueprintReadWrite)
	FString ToughnessStatTemp;

	UPROPERTY(BlueprintReadWrite)
	FString WoundsStatTemp;

	UPROPERTY(BlueprintReadWrite)
	FString InitiativeStatTemp;

	UPROPERTY(BlueprintReadWrite)
	FString AttacksStatTemp;

	UPROPERTY(BlueprintReadWrite)
	FString LeadershipStatTemp;

	UPROPERTY(BlueprintReadWrite)
	FString UnitStrengthStatTemp;

	UPROPERTY(BlueprintReadWrite)
	FString BaseCostStatTemp;

	UPROPERTY(BlueprintReadWrite)
	FString UnitSizeStatTemp;

    
};
