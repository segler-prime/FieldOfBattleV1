// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateArmy.h"
#include "SQLiteDatabase.h"

void UCreateArmy::GetWarbandUnits(FString InWarband)
{
    ////Open Database
    FoBDB = new FSQLiteDatabase();
    FoBDB->Open(*DBPath);

    //Build SQL Statement
    GetWarbandTable = new FSQLitePreparedStatement();
    FString GetWarbandUnitsSQL = FString::Printf(TEXT("SELECT * FROM Warband WHERE WarbandName IS '%s'"), *InWarband);
    GetWarbandTable->Create(*FoBDB, *GetWarbandUnitsSQL, ESQLitePreparedStatementFlags::Persistent);

    //Get Warband Info
    while (GetWarbandTable->Step() == ESQLitePreparedStatementStepResult::Row)
    {
        GetWarbandTable->GetColumnValueByName(TEXT("UnitName"), WarbandUnitInfo.UnitName);
        GetWarbandTable->GetColumnValueByName(TEXT("MoveStat"), WarbandUnitInfo.MoveStat);
        GetWarbandTable->GetColumnValueByName(TEXT("FightStat"), WarbandUnitInfo.FightStat);
        GetWarbandTable->GetColumnValueByName(TEXT("ShootStat"), WarbandUnitInfo.ShootStat);
        GetWarbandTable->GetColumnValueByName(TEXT("StrengthStat"), WarbandUnitInfo.StrengthStat);
        GetWarbandTable->GetColumnValueByName(TEXT("ToughnessStat"), WarbandUnitInfo.ToughnessStat);
        GetWarbandTable->GetColumnValueByName(TEXT("WoundsStat"), WarbandUnitInfo.WoundsStat);
        GetWarbandTable->GetColumnValueByName(TEXT("InitiativeStat"), WarbandUnitInfo.InitiativeStat);
        GetWarbandTable->GetColumnValueByName(TEXT("AttacksStat"), WarbandUnitInfo.AttacksStat);
        GetWarbandTable->GetColumnValueByName(TEXT("LeadershipStat"), WarbandUnitInfo.BraveryStat);
        GetWarbandTable->GetColumnValueByName(TEXT("UnitStrengthStat"), WarbandUnitInfo.UnitStrengthStat);
        GetWarbandTable->GetColumnValueByName(TEXT("BaseCostStat"), WarbandUnitInfo.BaseCostStat);

        AddAvailableUnitsToListview();
    }

    //Clean Up
    GetWarbandTable->Destroy();
    delete GetWarbandTable;
    FoBDB->Close();
    delete FoBDB;
}

int UCreateArmy::SaveArmyHeader(FString ArmyName, FString WarbandName)
{  
    //Open Database
    FoBDB = new FSQLiteDatabase();    
    FoBDB->Open(*DBPath);
    
    //Insert NewArmy Header Info
    InsertInArmyTable = new FSQLitePreparedStatement(); 
    FString InsertArmySQL = FString::Printf(TEXT("INSERT INTO Army (ArmyWarband, ArmyName, ArmyDescription, PlayerId) VALUES ('%s', '%s', 'A great army', 0001);"), *WarbandName, *ArmyName);
    InsertInArmyTable->Create(*FoBDB, *InsertArmySQL, ESQLitePreparedStatementFlags::Persistent);
    InsertInArmyTable->Execute();
    
    //Get the Army Id Info
    int ArmyId = FoBDB->GetLastInsertRowId();

    //Clean Up
    InsertInArmyTable->Destroy();
    delete InsertInArmyTable;
    FoBDB->Close();
    delete FoBDB;

    return ArmyId;
}

void UCreateArmy::SaveArmyUnits(FArmyUnitInfoStruct ArmyUnitInfo, FString ArmyId)
{
    //Open Database
    FoBDB = new FSQLiteDatabase();
    FoBDB->Open(*DBPath);
    
    //Build SQL Statement
    InsertInUnitTable = new FSQLitePreparedStatement(); 
    FString InsertUnitSQL = FString::Printf(TEXT("INSERT INTO Unit (UnitName, MoveStat, FightStat, ShootStat, StrengthStat, ToughnessStat, WoundsStat, InitiativeStat, AttacksStat, LeadershipStat, UnitStrengthStat, BaseCostStat, UnitSizeStat, ArmyId, PlayerId) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%d', '%d', '%s', 0001);"),
        *ArmyUnitInfo.UnitName, *ArmyUnitInfo.MoveStat, *ArmyUnitInfo.FightStat, *ArmyUnitInfo.ShootStat, *ArmyUnitInfo.StrengthStat, *ArmyUnitInfo.ToughnessStat, *ArmyUnitInfo.WoundsStat, *ArmyUnitInfo.InitiativeStat, *ArmyUnitInfo.AttacksStat, *ArmyUnitInfo.BraveryStat, *ArmyUnitInfo.UnitStrengthStat, ArmyUnitInfo.BaseCostStat, ArmyUnitInfo.UnitSizeStat, *ArmyId);
    InsertInUnitTable->Create(*FoBDB, *InsertUnitSQL, ESQLitePreparedStatementFlags::Persistent);
    
    //Insert New Army Info 
    InsertInUnitTable->Execute();
    
    //Clean Up
    InsertInUnitTable->Destroy();
    delete InsertInUnitTable;
    FoBDB->Close();
    delete FoBDB;
}

