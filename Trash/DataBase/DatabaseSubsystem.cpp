// Fill out your copyright notice in the Description page of Project Settings.


#include "DatabaseSubsystem.h"
#include "SQLiteDatabase.h"

void UDatabaseSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("UDatabaseSubsystem::Initialize - Starting"));
	

}

void UDatabaseSubsystem::Deinitialize()
{

	Super::Deinitialize();

	UE_LOG(LogTemp, Warning, TEXT("UDatabaseSubsystem::Deinitialize - Starting"));


}
