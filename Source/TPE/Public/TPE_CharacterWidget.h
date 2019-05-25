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
	void BindCharacterStat(class UTPECharacterStatComponent* NewCharacterStat, bool bPlayer);

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateHPWidget();

	void UpdateDamageWidget(int32 NewDamaged);

	void UpdateStaminaWidget();

	void UpdateBackWidget(class UProgressBar* BackProgressBar, float FrontProgressBarPercent, float InDeltaTime);

private:
	TWeakObjectPtr<class UTPECharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
		class UProgressBar* HPProgressBar;

	UPROPERTY()
		class UProgressBar* HPBackProgressBar;

	UPROPERTY()
		class UProgressBar* StaminaProgressBar;

	UPROPERTY()
		class UProgressBar* StaminaBackProgressBar;

	UPROPERTY()
		class UMultiLineEditableText* DamageEditableText;

	int32 HPDamaged = 0;

	bool bDamagedVisiblity = false;

	FTimerHandle TimerHandle;
};
