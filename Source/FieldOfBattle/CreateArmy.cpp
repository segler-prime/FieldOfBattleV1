// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateArmy.h"
#include "SQLiteDatabase.h"


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

void UCreateArmy::SaveArmyUnits(FString UnitName, 
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
                                FString ArmyId)
{
    
    //Open Database
    FoBDB = new FSQLiteDatabase();    
    FoBDB->Open(*DBPath);
    
    //Build SQL Statement
    InsertInUnitTable = new FSQLitePreparedStatement(); 
    FString InsertUnitSQL = FString::Printf(TEXT
        ("INSERT INTO Unit (UnitName, MoveStat, FightStat, ShootStat, StrengthStat, ToughnessStat, WoundsStat, InitiativeStat, AttacksStat, LeadershipStat, UnitStrengthStat, BaseCostStat, UnitSizeStat, ArmyId, PlayerId) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', 0001);"),
        *UnitName, *MoveStat, *FightStat, *ShootStat, *StrengthStat, *ToughnessStat, *WoundsStat, *InitiativeStat, *AttacksStat, *LeadershipStat, *UnitStrengthStat, *BaseCostStat, *UnitSizeStat, *ArmyId);
    
    InsertInUnitTable->Create(*FoBDB, *InsertUnitSQL, ESQLitePreparedStatementFlags::Persistent);
    
    //Insert New Army Info
    InsertInUnitTable->Execute();
    
    //Clean Up
    InsertInUnitTable->Destroy();
    delete InsertInUnitTable;
    FoBDB->Close();
    delete FoBDB;

}


void UCreateArmy::GetWarbandUnits(FString InWarband)
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
        GetWarbandTable->GetColumnValueByName(TEXT("UnitName"), UnitNameTemp);
        GetWarbandTable->GetColumnValueByName(TEXT("MoveStat"), MoveStatTemp);
        GetWarbandTable->GetColumnValueByName(TEXT("FightStat"), FightStatTemp);
        GetWarbandTable->GetColumnValueByName(TEXT("ShootStat"), ShootStatTemp);
        GetWarbandTable->GetColumnValueByName(TEXT("StrengthStat"), StrengthStatTemp);
        GetWarbandTable->GetColumnValueByName(TEXT("ToughnessStat"), ToughnessStatTemp);
        GetWarbandTable->GetColumnValueByName(TEXT("WoundsStat"), WoundsStatTemp);
        GetWarbandTable->GetColumnValueByName(TEXT("InitiativeStat"), InitiativeStatTemp);        
        GetWarbandTable->GetColumnValueByName(TEXT("AttacksStat"), AttacksStatTemp);
        GetWarbandTable->GetColumnValueByName(TEXT("LeadershipStat"), LeadershipStatTemp);
        GetWarbandTable->GetColumnValueByName(TEXT("UnitStrengthStat"), UnitStrengthStatTemp);
        GetWarbandTable->GetColumnValueByName(TEXT("BaseCostStat"), BaseCostStatTemp);

        AddAvailableUnitsToListview();
    }
    
    //Clean Up
    GetWarbandTable->Destroy();
    delete GetWarbandTable;
    FoBDB->Close();
    delete FoBDB;

}
