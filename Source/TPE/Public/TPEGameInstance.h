// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPE.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "TPEGameInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTPECharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FTPECharacterData() 
		: Level(1)
		, MaxHP(100.0f)
		, Attack(10.0f)
		, DropExp(10)
		, NextExp(30)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Attack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;
};

UCLASS()
class TPE_API UTPEGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	
public:
	UTPEGameInstance();
	
	virtual void Init() override;

	FTPECharacterData* GetTPEChacracterData(int32 Level);

private:

	UPROPERTY()
	class UDataTable* TPECharacterTable;
};
