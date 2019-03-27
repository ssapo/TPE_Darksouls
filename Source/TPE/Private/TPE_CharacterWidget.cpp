// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_CharacterWidget.h"
#include "TPECharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UTPE_CharacterWidget::BindCharacterStat(UTPECharacterStatComponent* NewCharacterStat)
{
	TPE_CHECK(nullptr != NewCharacterStat);

	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddUObject(this, &UTPE_CharacterWidget::UpdateHPWidget);
	NewCharacterStat->OnStaminaChanged.AddUObject(this, &UTPE_CharacterWidget::UpdateStaminaWidget);
}

void UTPE_CharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	TPE_CHECK(nullptr != HPProgressBar);

	StaminaProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_StaminaBar")));
	TPE_CHECK(nullptr != StaminaProgressBar);
	UpdateHPWidget();
}

void UTPE_CharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}

void UTPE_CharacterWidget::UpdateStaminaWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (nullptr != StaminaProgressBar)
		{
			StaminaProgressBar->SetPercent(CurrentCharacterStat->GetStaminaRatio());
		}
	}
}