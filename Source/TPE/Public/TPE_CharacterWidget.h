// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPE.h"
#include "Blueprint/UserWidget.h"
#include "TPE_CharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPE_API UTPE_CharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UTPECharacterStatComponent* NewCharacterStat);

protected:
	virtual void NativeConstruct() override;

	void UpdateHPWidget();

private:
	TWeakObjectPtr<class UTPECharacterStatComponent> CurrentCharacterStat;
	
	UPROPERTY()
	class UProgressBar* HPProgressBar;
	
};
