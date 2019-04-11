// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_CharacterWidget.h"
#include "TPECharacterStatComponent.h"
#include "Components/ProgressBar.h"
#include "Components/ScaleBox.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UTPE_CharacterWidget::BindCharacterStat(UTPECharacterStatComponent* NewCharacterStat, bool bPlayer)
{
	TPE_CHECK(nullptr != NewCharacterStat);

	CurrentCharacterStat = NewCharacterStat;
	CurrentCharacterStat->OnHPChanged.AddUObject(this, &UTPE_CharacterWidget::UpdateHPWidget);
	CurrentCharacterStat->OnStaminaChanged.AddUObject(this, &UTPE_CharacterWidget::UpdateStaminaWidget);

	auto StaminaCanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("CP_Stamina")));
	TPE_CHECK(nullptr != StaminaCanvasPanel);

	StaminaCanvasPanel->SetVisibility(bPlayer ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

	auto HPScaleBox = Cast<UScaleBox>(GetWidgetFromName(TEXT("SB_HP")));
	TPE_CHECK(nullptr != HPScaleBox);

	auto HPCanvasPanelSlot = Cast<UCanvasPanelSlot>(HPScaleBox->Slot);
	TPE_CHECK(nullptr != HPCanvasPanelSlot);

	HPCanvasPanelSlot->SetSize(bPlayer ? FVector2D(CurrentCharacterStat->GetMaxHP()/2.0f, 10.0f) : FVector2D(300.0f, 10.0f));

	UpdateHPWidget();
	UpdateStaminaWidget();
}

void UTPE_CharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	TPE_CHECK(nullptr != HPProgressBar);

	HPBackProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBack")));
	TPE_CHECK(nullptr != HPBackProgressBar);

	HPBackProgressBar->SetPercent(1.0f);
	
	UpdateHPWidget();

	StaminaProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_StaminaBar")));
	TPE_CHECK(nullptr != StaminaProgressBar);

	StaminaBackProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_StaminaBack")));
	TPE_CHECK(nullptr != StaminaBackProgressBar);

	StaminaBackProgressBar->SetPercent(1.0f);
	
	UpdateStaminaWidget();
}

void UTPE_CharacterWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (HPProgressBar && HPProgressBar->IsVisible())
	{
		UpdateBackWidget(HPBackProgressBar, HPProgressBar->Percent, InDeltaTime);
	}

	if (StaminaProgressBar && StaminaProgressBar->IsVisible())
	{
		UpdateBackWidget(StaminaBackProgressBar, StaminaProgressBar->Percent, InDeltaTime);
	}
}

void UTPE_CharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}

		if (nullptr != HPBackProgressBar)
		{
			if (CurrentCharacterStat->GetStaminaRatio() > HPBackProgressBar->Percent)
			{
				HPBackProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
			}
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

		if (nullptr != StaminaBackProgressBar)
		{
			if (CurrentCharacterStat->GetStaminaRatio() > StaminaBackProgressBar->Percent)
			{
				StaminaBackProgressBar->SetPercent(CurrentCharacterStat->GetStaminaRatio());
			}
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