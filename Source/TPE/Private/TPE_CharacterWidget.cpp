// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_CharacterWidget.h"
#include "TPECharacterStatComponent.h"
#include "Components/ProgressBar.h"
#include "Components/ScaleBox.h"

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

	HPBackProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBack")));
	TPE_CHECK(nullptr != HPBackProgressBar);

	HPBackProgressBar->SetPercent(1.0f);
	
	HPScaleBox = Cast<UScaleBox>(GetWidgetFromName(TEXT("SB_HP")));
	TPE_CHECK(nullptr != HPScaleBox);

	//HPScaleBox->GetCachedGeometry().GetLocalSize();

	UpdateHPWidget();
	
	StaminaProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_StaminaBar")));
	TPE_CHECK(nullptr != StaminaProgressBar);

	StaminaBackProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_StaminaBack")));
	TPE_CHECK(nullptr != StaminaBackProgressBar);

	StaminaBackProgressBar->SetPercent(1.0f);
	
	StaminaScaleBox = Cast<UScaleBox>(GetWidgetFromName(TEXT("SB_Stamina")));
	TPE_CHECK(nullptr != StaminaScaleBox);

	UpdateStaminaWidget();
}

void UTPE_CharacterWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	TPE_CHECK(nullptr != HPProgressBar);
	TPE_CHECK(nullptr != HPBackProgressBar);

	UpdateBackWidget(HPBackProgressBar, HPProgressBar->Percent, InDeltaTime);

	TPE_CHECK(nullptr != StaminaProgressBar);
	TPE_CHECK(nullptr != StaminaBackProgressBar);

	UpdateBackWidget(StaminaBackProgressBar, StaminaProgressBar->Percent, InDeltaTime);
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

void UTPE_CharacterWidget::UpdateBackWidget(UProgressBar* BackProgressBar, float FrontProgressBarPercent, float InDeltaTime)
{
	if (nullptr == BackProgressBar) { return; }

	float BackPercent = BackProgressBar->Percent;
	float LeftPercent = BackPercent - FrontProgressBarPercent;

	if (0 < LeftPercent)
	{
		float PercentAmount = 0.2f * InDeltaTime;
		PercentAmount = (LeftPercent < PercentAmount) ? LeftPercent : PercentAmount;

		float NextBackPercent = BackPercent - PercentAmount;
		BackProgressBar->SetPercent(NextBackPercent);
	}
}