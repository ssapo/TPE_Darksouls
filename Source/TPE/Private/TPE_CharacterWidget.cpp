// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_CharacterWidget.h"
#include "TPECharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UTPE_CharacterWidget::BindCharacterStat(UTPECharacterStatComponent* NewCharacterStat)
{
	TPE_CHECK(nullptr != NewCharacterStat);

	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddLambda([this]() -> void {
		if (CurrentCharacterStat.IsValid())
		{
			TPE_LOG(Warning, "HPRatio : %f", CurrentCharacterStat->GetHPRatio());
		}
	});
}

void UTPE_CharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	TPE_CHECK(nullptr != HPProgressBar);
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