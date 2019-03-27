// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_PlayerController.h"
#include "Components/WidgetComponent.h"
#include "TPE_CharacterWidget.h"

ATPE_PlayerController::ATPE_PlayerController()
{
	OnScreenControls = CreateDefaultSubobject<UWidgetComponent>(TEXT("ONSCREENCONTROLS"));

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_ONSCREENCONTROLS(TEXT("/Game/TPE/Blueprints/UI/UI_PlayerOnScreenControls.UI_PlayerOnScreenControls_C"));

	if (UI_ONSCREENCONTROLS.Succeeded())
	{
		OnScreenControls->SetWidgetClass(UI_ONSCREENCONTROLS.Class);
	}
}

void ATPE_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr != OnScreenControls)
	{
		auto UserWidget = OnScreenControls->GetUserWidgetObject();
		if (UserWidget)
		{
			UserWidget->AddToViewport();
		}
	}
}

void ATPE_PlayerController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
}

void ATPE_PlayerController::UnPossess()
{
	Super::UnPossess();
}