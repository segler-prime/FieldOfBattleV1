// Fill out your copyright notice in the Description page of Project Settings.


#include "Army.h"
#include "SQLiteDatabase.h"

TArray<FWarbandUnitInfoStruct> UArmy::GetWarbandUnits(FString InWarband)
{
    //Open Database
    FoBDB = new FSQLiteDatabase();
    FoBDB->Open(*DBPath);

    //Build SQL Statement
    WarbandUnitTable = new FSQLitePreparedStatement();
    FString GetWarbandUnitsSQL = FString::Printf(TEXT("SELECT * FROM WarbandUnit WHERE WarbandName IS '%s'"), *InWarband);
    WarbandUnitTable->Create(*FoBDB, *GetWarbandUnitsSQL, ESQLitePreparedStatementFlags::Persistent);

    TArray<FWarbandUnitInfoStruct> WarbandUnitInfoArray;
    FWarbandUnitInfoStruct WarbandUnitInfo;

    //Get Warband Unit Info
    while (WarbandUnitTable->Step() == ESQLitePreparedStatementStepResult::Row)
    {
        WarbandUnitTable->GetColumnValueByName(TEXT("UnitName"), WarbandUnitInfo.UnitName);
        WarbandUnitTable->GetColumnValueByName(TEXT("MoveStat"), WarbandUnitInfo.MoveStat);
        WarbandUnitTable->GetColumnValueByName(TEXT("FightStat"), WarbandUnitInfo.FightStat);
        WarbandUnitTable->GetColumnValueByName(TEXT("ShootStat"), WarbandUnitInfo.ShootStat);
        WarbandUnitTable->GetColumnValueByName(TEXT("AttacksStat"), WarbandUnitInfo.AttacksStat);
        WarbandUnitTable->GetColumnValueByName(TEXT("ToughnessStat"), WarbandUnitInfo.ToughnessStat);
        WarbandUnitTable->GetColumnValueByName(TEXT("WoundsStat"), WarbandUnitInfo.WoundsStat);
        WarbandUnitTable->GetColumnValueByName(TEXT("StrengthStat"), WarbandUnitInfo.StrengthStat);
        WarbandUnitTable->GetColumnValueByName(TEXT("BraveryStat"), WarbandUnitInfo.BraveryStat);
        WarbandUnitTable->GetColumnValueByName(TEXT("InitiativeStat"), WarbandUnitInfo.InitiativeStat);
        WarbandUnitTable->GetColumnValueByName(TEXT("UnitStrengthStat"), WarbandUnitInfo.UnitStrengthStat);
        WarbandUnitTable->GetColumnValueByName(TEXT("BaseCostStat"), WarbandUnitInfo.BaseCostStat);
        WarbandUnitTable->GetColumnValueByName(TEXT("UnitSpacingStat"), WarbandUnitInfo.UnitSpacingStat);
        WarbandUnitTable->GetColumnValueByName(TEXT("UnitWidthStat"), WarbandUnitInfo.UnitWidthStat);
        WarbandUnitInfoArray.Add(WarbandUnitInfo);
    }

    //Clean Up
    WarbandUnitTable->Destroy();
    delete WarbandUnitTable;
    FoBDB->Close();
    delete FoBDB;

    return WarbandUnitInfoArray;
}

TArray<FArmyHeaderInfoStruct> UArmy::GetArmyHeaders()
{
    //Open Database
    FoBDB = new FSQLiteDatabase();
    FoBDB->Open(*DBPath);

    //Build SQL Statement
    ArmyHeadersTable = new FSQLitePreparedStatement();
    FString GetArmyHeadersSQL = FString::Printf(TEXT("SELECT * FROM ArmyHeader"));
    ArmyHeadersTable->Create(*FoBDB, *GetArmyHeadersSQL, ESQLitePreparedStatementFlags::Persistent);

    TArray<FArmyHeaderInfoStruct> ArmyHeaderInfoArray;
    FArmyHeaderInfoStruct ArmyHeaderInfo;

    //Load the Army Headers
    while (ArmyHeadersTable->Step() == ESQLitePreparedStatementStepResult::Row)
    {
        ArmyHeadersTable->GetColumnValueByName(TEXT("ArmyId"), ArmyHeaderInfo.ArmyID);
        ArmyHeadersTable->GetColumnValueByName(TEXT("ArmyWarband"), ArmyHeaderInfo.ArmyWarband);
        ArmyHeadersTable->GetColumnValueByName(TEXT("ArmyName"), ArmyHeaderInfo.ArmyName);
        ArmyHeadersTable->GetColumnValueByName(TEXT("ArmyDescription"), ArmyHeaderInfo.ArmyDescription);
        ArmyHeadersTable->GetColumnValueByName(TEXT("ArmyPoints"), ArmyHeaderInfo.ArmyPoints);
        ArmyHeadersTable->GetColumnValueByName(TEXT("PlayerId"), ArmyHeaderInfo.PlayerID);
        ArmyHeaderInfoArray.Add(ArmyHeaderInfo);
    }

    //Clean Up
    ArmyHeadersTable->Destroy();
    delete  ArmyHeadersTable;
    FoBDB->Close();
    delete FoBDB;

    return ArmyHeaderInfoArray;
}

TArray<FArmyUnitInfoStruct> UArmy::GetArmyUnits(FString InArmyID)
{
    //Open Database
    FoBDB = new FSQLiteDatabase();
    FoBDB->Open(*DBPath);

    //Build SQL Statement
    ArmyUnitsTable = new FSQLitePreparedStatement();
    FString GetArmyUnitsSQL = FString::Printf(TEXT("SELECT * FROM ArmyUnit WHERE ArmyId IS '%s'"), *InArmyID);
    ArmyUnitsTable->Create(*FoBDB, *GetArmyUnitsSQL, ESQLitePreparedStatementFlags::Persistent);

    TArray<FArmyUnitInfoStruct> ArmyUnitInfoArray;
    FArmyUnitInfoStruct ArmyUnitInfo;

    //Get Army Unit Info
    while (ArmyUnitsTable->Step() == ESQLitePreparedStatementStepResult::Row)
    {
        ArmyUnitsTable->GetColumnValueByName(TEXT("UnitId"), ArmyUnitInfo.UnitId);
        ArmyUnitsTable->GetColumnValueByName(TEXT("UnitName"), ArmyUnitInfo.UnitName);
        ArmyUnitsTable->GetColumnValueByName(TEXT("MoveStat"), ArmyUnitInfo.MoveStat);
        ArmyUnitsTable->GetColumnValueByName(TEXT("FightStat"), ArmyUnitInfo.FightStat);
        ArmyUnitsTable->GetColumnValueByName(TEXT("ShootStat"), ArmyUnitInfo.ShootStat);
        ArmyUnitsTable->GetColumnValueByName(TEXT("AttacksStat"), ArmyUnitInfo.AttacksStat);
        ArmyUnitsTable->GetColumnValueByName(TEXT("ToughnessStat"), ArmyUnitInfo.ToughnessStat);
        ArmyUnitsTable->GetColumnValueByName(TEXT("WoundsStat"), ArmyUnitInfo.WoundsStat);
        ArmyUnitsTable->GetColumnValueByName(TEXT("StrengthStat"), ArmyUnitInfo.StrengthStat);
        ArmyUnitsTable->GetColumnValueByName(TEXT("BraveryStat"), ArmyUnitInfo.BraveryStat);
        ArmyUnitsTable->GetColumnValueByName(TEXT("InitiativeStat"), ArmyUnitInfo.InitiativeStat);
        ArmyUnitsTable->GetColumnValueByName(TEXT("UnitStrengthStat"), ArmyUnitInfo.UnitStrengthStat);
        ArmyUnitsTable->GetColumnValueByName(TEXT("BaseCostStat"), ArmyUnitInfo.BaseCostStat);
        ArmyUnitsTable->GetColumnValueByName(TEXT("UnitSpacingStat"), ArmyUnitInfo.UnitSpacingStat);
        ArmyUnitsTable->GetColumnValueByName(TEXT("UnitWidthStat"), ArmyUnitInfo.UnitWidthStat);
        ArmyUnitsTable->GetColumnValueByName(TEXT("UnitSizeStat"), ArmyUnitInfo.UnitSizeStat);
        ArmyUnitsTable->GetColumnValueByName(TEXT("UnitDamageStat"), ArmyUnitInfo.UnitDamageStat);
        ArmyUnitsTable->GetColumnValueByName(TEXT("UnitTeam"), ArmyUnitInfo.UnitTeam);
        ArmyUnitsTable->GetColumnValueByName(TEXT("UnitOwner"), ArmyUnitInfo.UnitOwner);
        ArmyUnitInfoArray.Add(ArmyUnitInfo);
    }

    //Clean Up
    ArmyUnitsTable->Destroy();
    delete ArmyUnitsTable;
    FoBDB->Close();
    delete FoBDB;

    return ArmyUnitInfoArray;
}

int UArmy::SaveArmyHeader(FArmyHeaderInfoStruct NewArmyHeaderInfo)
{
    //UE_LOG(LogTemp, Warning, TEXT("UArmy::SaveArmyHeader - Starting"));
        
    //Open Database
    FoBDB = new FSQLiteDatabase();    
    FoBDB->Open(*DBPath);

    //Insert New Army Header Info
    InsertInArmyHeaderTable = new FSQLitePreparedStatement();
    FString InsertArmyHeaderSQL = FString::Printf(TEXT("INSERT INTO ArmyHeader (ArmyWarband, ArmyName, ArmyDescription, ArmyPoints, PlayerId) VALUES ('%s', '%s', 'A great army', '%s', 0001);"), *NewArmyHeaderInfo.ArmyWarband, *NewArmyHeaderInfo.ArmyName, *NewArmyHeaderInfo.ArmyPoints);
    InsertInArmyHeaderTable->Create(*FoBDB, *InsertArmyHeaderSQL, ESQLitePreparedStatementFlags::Persistent);
    InsertInArmyHeaderTable->Execute();

    //Get the Army Id Info
    int ArmyId = FoBDB->GetLastInsertRowId();

    //Clean Up
    InsertInArmyHeaderTable->Destroy();
    delete InsertInArmyHeaderTable;
    FoBDB->Close();
    delete FoBDB;

    return ArmyId;
}

void UArmy::SaveArmyUnits(FArmyUnitInfoStruct NewArmyUnitInfo, FString NewArmyID)
{
    
    //UE_LOG(LogTemp, Warning, TEXT("UArmy::SaveArmyUnits - Starting"));

    //Open Database
    FoBDB = new FSQLiteDatabase();
    FoBDB->Open(*DBPath);

    //Build SQL Statement
    InsertInArmyUnitTable = new FSQLitePreparedStatement();
    FString InsertArmyUnitSQL = FString::Printf(TEXT
    ("INSERT INTO ArmyUnit (UnitName, MoveStat, FightStat, ShootStat, AttacksStat, ToughnessStat, WoundsStat, StrengthStat, BraveryStat, InitiativeStat, UnitStrengthStat, BaseCostStat, UnitSpacingStat, UnitWidthStat, UnitSizeStat, UnitDamageStat, UnitTeam, UnitOwner, ArmyId, PlayerId) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%d', '%d', '%d', '%d', '%d', '%d', '%s', '%s', 0001);"),
        *NewArmyUnitInfo.UnitName, *NewArmyUnitInfo.MoveStat, *NewArmyUnitInfo.FightStat, *NewArmyUnitInfo.ShootStat, *NewArmyUnitInfo.AttacksStat, *NewArmyUnitInfo.ToughnessStat, *NewArmyUnitInfo.WoundsStat, *NewArmyUnitInfo.StrengthStat, *NewArmyUnitInfo.BraveryStat, *NewArmyUnitInfo.InitiativeStat, *NewArmyUnitInfo.UnitStrengthStat, NewArmyUnitInfo.BaseCostStat, NewArmyUnitInfo.UnitSpacingStat, NewArmyUnitInfo.UnitWidthStat, NewArmyUnitInfo.UnitSizeStat, NewArmyUnitInfo.UnitDamageStat, NewArmyUnitInfo.UnitTeam, *NewArmyUnitInfo.UnitOwner, *NewArmyID);
     
    InsertInArmyUnitTable->Create(*FoBDB, *InsertArmyUnitSQL, ESQLitePreparedStatementFlags::Persistent);

    //Insert New Army Info 
    InsertInArmyUnitTable->Execute();

    //Clean Up
    InsertInArmyUnitTable->Destroy();
    delete InsertInArmyUnitTable;
    FoBDB->Close();
    delete FoBDB;
}

void UArmy::DeleteArmy(FString ArmyID)
{
    //Open Database
    FoBDB = new FSQLiteDatabase();
    FoBDB->Open(*DBPath);

    //Build SQL Statements
    DeleteArmyHeaderStmt = new FSQLitePreparedStatement();
    FString DeleteArmyHeaderSQL = FString::Printf(TEXT("DELETE FROM ArmyHeader WHERE ArmyId=%s"), *ArmyID);
    DeleteArmyHeaderStmt->Create(*FoBDB, *DeleteArmyHeaderSQL, ESQLitePreparedStatementFlags::Persistent);

    //Delete the Army
    DeleteArmyHeaderStmt->Execute();

    //Clean Up
    DeleteArmyHeaderStmt->Destroy();
    delete DeleteArmyHeaderStmt;
    FoBDB->Close();
    delete FoBDB;

    DeleteArmyUnits(ArmyID);
}

void UArmy::DeleteArmyUnits(FString ArmyID)
{
    //Open Database
    FoBDB = new FSQLiteDatabase();
    FoBDB->Open(*DBPath);

    //Build SQL Statements
    DeleteArmyUnitsStmt = new FSQLitePreparedStatement();
    FString DeleteArmyUnitsSQL = FString::Printf(TEXT("DELETE FROM ArmyUnit WHERE ArmyId='%s'"), *ArmyID);
    DeleteArmyUnitsStmt->Create(*FoBDB, *DeleteArmyUnitsSQL, ESQLitePreparedStatementFlags::Persistent);

    //Delete the Army
    DeleteArmyUnitsStmt->Execute();

    //Clean Up
    DeleteArmyUnitsStmt->Destroy();
    delete DeleteArmyUnitsStmt;
    FoBDB->Close();
    delete FoBDB;
}