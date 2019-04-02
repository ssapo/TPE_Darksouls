// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_PlayerController.h"
#include "Components/WidgetComponent.h"
#include "TPE_CharacterWidget.h"
#include "TPE_Character.h"

ATPE_PlayerController::ATPE_PlayerController()
{
	OnScreenControls = CreateDefaultSubobject<UWidgetComponent>(TEXT("ONSCREENCONTROLS"));

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_ONSCREENCONTROLS(TEXT("/Game/TPE/Blueprints/UI/UI_PlayerOnScreenControls.UI_PlayerOnScreenControls_C"));

	if (UI_ONSCREENCONTROLS.Succeeded())
	{
		OnScreenControls->SetWidgetClass(UI_ONSCREENCONTROLS.Class);

		OnScreenControls->SetVisibility(false);
	}
}

void ATPE_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr != OnScreenControls)
	{
		auto UserWidget = OnScreenControls->GetUserWidgetObject();
		if (nullptr != UserWidget)
		{
			auto StatBar = Cast<UTPE_CharacterWidget>(UserWidget->GetWidgetFromName(TEXT("StatBar")));
			if (nullptr != StatBar)
			{
				StatBar->BindCharacterStat(ControllingCharacterStat);

				UserWidget->AddToViewport();

				OnScreenControls->SetVisibility(true);
			}
		}
	}
}

void ATPE_PlayerController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	auto Character = Cast<ATPE_Character>(InPawn);
	if (nullptr != Character)
	{
		ControllingCharacter = Character;
	}

	auto StatComponent = ControllingCharacter->GetStatComponent();
	if (nullptr != StatComponent)
	{
		ControllingCharacterStat = ControllingCharacter->GetStatComponent();
	}
}

void ATPE_PlayerController::UnPossess()
{
	Super::UnPossess();

	ControllingCharacter = nullptr;

	ControllingCharacterStat = nullptr;

	OnScreenControls->SetVisibility(false);
}