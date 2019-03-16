// Fill out your copyright notice in the Description page of Project Settings.

#include "TPEGameInstance.h"

UTPEGameInstance::UTPEGameInstance()
{
	FString CharacterDataPath = TEXT("/Game/TPE/GameData/TPECharacterCSV.TPECharacterCSV");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_TPECHARACTER(*CharacterDataPath);

	TPE_CHECK(DT_TPECHARACTER.Succeeded());

	TPECharacterTable = DT_TPECHARACTER.Object;
	TPE_CHECK(TPECharacterTable->RowMap.Num() > 0);
}

void UTPEGameInstance::Init()
{
	Super::Init();
	TPE_LOG_S(Warning);
}

FTPECharacterData* UTPEGameInstance::GetTPEChacracterData(int32 Level)
{
	return TPECharacterTable->FindRow<FTPECharacterData>(*FString::FromInt(Level), TEXT(""));
}
