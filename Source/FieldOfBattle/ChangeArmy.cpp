// Fill out your copyright notice in the Description page of Project Settings.

#include "ChangeArmy.h"
#include "SQLiteDatabase.h"
#include "Components/ComboBoxString.h"
#include "Components/ListView.h"

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
        GetArmyNames->GetColumnValueByName(TEXT("ArmyName"), ArmyNameTemp);
        GetArmyNames->GetColumnValueByName(TEXT("ArmyWarband"), WarbandTemp);
        GetArmyNames->GetColumnValueByName(TEXT("ArmyId"), ArmyIdTemp);
        AddArmyToListview(); 
    }

    //Clean Up
    GetArmyNames->Destroy();
    delete GetArmyNames;
    FoBDB->Close();
    delete FoBDB;
}

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

        AddWarbandUnitsToListview(); 
    }
    
    //Clean Up
    GetWarbandTable->Destroy();
    delete GetWarbandTable;
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
        GetArmyUnitsTable->GetColumnValueByName(TEXT("UnitName"), UnitNameTemp);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("MoveStat"), MoveStatTemp);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("FightStat"), FightStatTemp);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("ShootStat"), ShootStatTemp);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("StrengthStat"), StrengthStatTemp);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("ToughnessStat"), ToughnessStatTemp);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("WoundsStat"), WoundsStatTemp);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("InitiativeStat"), InitiativeStatTemp);        
        GetArmyUnitsTable->GetColumnValueByName(TEXT("AttacksStat"), AttacksStatTemp);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("LeadershipStat"), LeadershipStatTemp);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("UnitStrengthStat"), UnitStrengthStatTemp);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("BaseCostStat"), BaseCostStatTemp);
        GetArmyUnitsTable->GetColumnValueByName(TEXT("UnitSizeStat"), UnitSizeStatTemp);

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

void UChangeArmy::SaveArmyUnits(FString UnitName, 
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

