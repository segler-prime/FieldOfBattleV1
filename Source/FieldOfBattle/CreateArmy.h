// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

public:


protected:

	UFUNCTION(BlueprintCallable)
		int SaveArmyHeader(FString ArmyName,
			FString WarbandName);

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

	UFUNCTION(BlueprintCallable)
		void GetWarbandUnits(FString InWarband);

	UFUNCTION(BlueprintImplementableEvent)
		void AddAvailableUnitsToListview();

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

private:

	FSQLiteDatabase * FoBDB;
	FString DBPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() + "Database/FoB.db");
	FSQLitePreparedStatement * InsertInArmyTable;
	FSQLitePreparedStatement * InsertInUnitTable;
	FSQLitePreparedStatement * GetWarbandTable;
	FSQLitePreparedStatement * GetNewArmyId;



};
