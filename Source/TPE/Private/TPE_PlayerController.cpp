// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_PlayerController.h"
#include "Components/WidgetComponent.h"
#include "TPE_CharacterWidget.h"
#include "TPE_Character.h"
#include "TPECharacterStatComponent.h"

ATPE_PlayerController::ATPE_PlayerController()
{
}

void ATPE_PlayerController::OnPossess(APawn* aPwan)
{
	Super::OnPossess(aPwan);

	auto TPECharacter = Cast<ATPE_Character>(aPwan);
	TPE_CHECK(nullptr != TPECharacter);

	auto StatComponent = TPECharacter->GetStatComponent();
	TPE_CHECK(nullptr != StatComponent);

	StatComponent->SetNewLevel(5);
}