// Fill out your copyright notice in the Description page of Project Settings.

#include "ChangeArmy.h"
#include "SQLiteDatabase.h"
#include "Components/ComboBoxString.h"
#include "Components/ListView.h"

void UChangeArmy::GetWarbandUnits(FString InWarband)
{
    //Open Database
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

        AddWarbandUnitsToListview();
    }

    //Clean Up
    GetWarbandTable->Destroy();
    delete GetWarbandTable;
    FoBDB->Close();
    delete FoBDB;
}

void UChangeArmy::GetArmy()
{
    //Open Database
    FoBDB = new FSQLiteDatabase();    
    FoBDB->Open(*DBPath);
        
    //Build SQL Statement
    GetArmyNames = new FSQLitePreparedStatement(); 
    FString GetArmyNamesSQL = FString::Printf(TEXT("SELECT * FROM Army"));
    GetArmyNames->Create(*FoBDB, *GetArmyNamesSQL, ESQLitePreparedStatementFlags::Persistent);
    
    //Load the Army Names 
    while (GetArmyNames->Step() == ESQLitePreparedStatementStepResult::Row)
    {
        GetArmyNames->GetColumnValueByName(TEXT("ArmyName"), ArmyInfo.ArmyName);
        GetArmyNames->GetColumnValueByName(TEXT("ArmyWarband"), ArmyInfo.ArmyWarband);
        GetArmyNames->GetColumnValueByName(TEXT("ArmyId"), ArmyInfo.ArmyID);
        AddArmyToListview(); 
    }

    //Clean Up
    GetArmyNames->Destroy();
    delete GetArmyNames;
    FoBDB->Close();
    delete FoBDB;
}

void UChangeArmy::GetArmyUnits(FString InArmyId)
{
    //Open Database
    FoBDB = new FSQLiteDatabase();    
    FoBDB->Open(*DBPath);
    
    //Build SQL Statement
    GetArmyUnitsTable = new FSQLitePreparedStatement(); 
    FString GetArmyUnitsSQL = FString::Printf(TEXT("SELECT * FROM Unit WHERE ArmyId IS '%s'"), *InArmyId);
    GetArmyUnitsTable->Create(*FoBDB, *GetArmyUnitsSQL, ESQLitePreparedStatementFlags::Persistent);

    //Get Army Unit Info
    while (GetArmyUnitsTable->Step() == ESQLitePreparedStatementStepResult::Row)
    {
        GetArmyUnitsTable->GetColumnValueByName(TEXT("UnitName"), ArmyUnitInfo.UnitName);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("MoveStat"), ArmyUnitInfo.MoveStat);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("FightStat"), ArmyUnitInfo.FightStat);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("ShootStat"), ArmyUnitInfo.ShootStat);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("StrengthStat"), ArmyUnitInfo.StrengthStat);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("ToughnessStat"), ArmyUnitInfo.ToughnessStat);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("WoundsStat"), ArmyUnitInfo.WoundsStat);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("InitiativeStat"), ArmyUnitInfo.InitiativeStat);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("AttacksStat"), ArmyUnitInfo.AttacksStat);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("LeadershipStat"), ArmyUnitInfo.BraveryStat);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("UnitStrengthStat"), ArmyUnitInfo.UnitStrengthStat);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("BaseCostStat"), ArmyUnitInfo.BaseCostStat);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("UnitSizeStat"), ArmyUnitInfo.UnitSizeStat);

        AddArmyUnitsToListview(); 
    }
    
    //Clean Up
    GetArmyUnitsTable->Destroy();
    delete GetArmyUnitsTable;
    FoBDB->Close();
    delete FoBDB;
}

void UChangeArmy::DeleteArmy(FString ArmyId)
{
    //Open Database
    FoBDB = new FSQLiteDatabase();    
    FoBDB->Open(*DBPath);
        
    //Build SQL Statements
    DeleteArmyStatement = new FSQLitePreparedStatement(); 
    FString DeleteArmySQL = FString::Printf(TEXT("DELETE FROM Army WHERE ArmyId=%s"), *ArmyId);
    DeleteArmyStatement->Create(*FoBDB, *DeleteArmySQL, ESQLitePreparedStatementFlags::Persistent);
    
    DeleteArmyUnitsStatement = new FSQLitePreparedStatement(); 
    FString DeleteArmyUnitsSQL = FString::Printf(TEXT("DELETE FROM Unit WHERE ArmyId='%s'"), *ArmyId);
    DeleteArmyUnitsStatement->Create(*FoBDB, *DeleteArmyUnitsSQL, ESQLitePreparedStatementFlags::Persistent);
    
    //Delete the Army
    DeleteArmyStatement->Execute();
    DeleteArmyUnitsStatement->Execute();

    //Clean Up
    DeleteArmyStatement->Destroy();
    delete DeleteArmyStatement;
    DeleteArmyUnitsStatement->Destroy();
    delete DeleteArmyUnitsStatement;
    FoBDB->Close();
    delete FoBDB;
}

void UChangeArmy::DeleteArmyUnits(FString ArmyId)
{
    //Open Database
    FoBDB = new FSQLiteDatabase();    
    FoBDB->Open(*DBPath);
        
    //Build SQL Statements
    DeleteArmyUnitsStatement = new FSQLitePreparedStatement(); 
    FString DeleteArmyUnitsSQL = FString::Printf(TEXT("DELETE FROM Unit WHERE ArmyId='%s'"), *ArmyId);
    DeleteArmyUnitsStatement->Create(*FoBDB, *DeleteArmyUnitsSQL, ESQLitePreparedStatementFlags::Persistent);
    
    //Delete the Army
    DeleteArmyUnitsStatement->Execute();

    //Clean Up
    DeleteArmyUnitsStatement->Destroy();
    delete DeleteArmyUnitsStatement;
    FoBDB->Close();
    delete FoBDB;
}

void UChangeArmy::SaveArmyUnits(FArmyUnitInfoStruct NewArmyUnitInfo, FString NewArmyId)
{
    //Open Database
    FoBDB = new FSQLiteDatabase();    
    FoBDB->Open(*DBPath);
    
    //Build SQL Statement
    InsertInUnitTable = new FSQLitePreparedStatement(); 
    FString InsertUnitSQL = FString::Printf(TEXT
        ("INSERT INTO Unit (UnitName, MoveStat, FightStat, ShootStat, StrengthStat, ToughnessStat, WoundsStat, InitiativeStat, AttacksStat, LeadershipStat, UnitStrengthStat, BaseCostStat, UnitSizeStat, ArmyId, PlayerId) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%d', '%d', '%s', 0001);"),
        *NewArmyUnitInfo.UnitName, *NewArmyUnitInfo.MoveStat, *NewArmyUnitInfo.FightStat, *NewArmyUnitInfo.ShootStat, *NewArmyUnitInfo.StrengthStat, *NewArmyUnitInfo.ToughnessStat, *NewArmyUnitInfo.WoundsStat, *NewArmyUnitInfo.InitiativeStat, *NewArmyUnitInfo.AttacksStat, *NewArmyUnitInfo.BraveryStat, *NewArmyUnitInfo.UnitStrengthStat, NewArmyUnitInfo.BaseCostStat, NewArmyUnitInfo.UnitSizeStat, *NewArmyId);
    
    InsertInUnitTable->Create(*FoBDB, *InsertUnitSQL, ESQLitePreparedStatementFlags::Persistent);
    
    //Insert New Army Info
    InsertInUnitTable->Execute();
  
    //Clean Up
    InsertInUnitTable->Destroy();
    delete InsertInUnitTable;
    FoBDB->Close();
    delete FoBDB;
}

