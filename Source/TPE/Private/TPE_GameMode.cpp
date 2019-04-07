// Fill out your copyright notice in the Description page of Project Settings.


#include "TPE_GameMode.h"
#include "TPE_PlayerController.h"
#include "TPE_Actor.h"
#include "TPE_Character.h"
#include "GameFramework/HUD.h"

ATPE_GameMode::ATPE_GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnFound (TEXT("/Game/TPE/Blueprints/TwinSwordCharacterBP.TwinSwordCharacterBP_C"));

	if (DefaultPawnFound.Succeeded())
	{
		DefaultPawnClass = DefaultPawnFound.Class;
	}

	static ConstructorHelpers::FClassFinder<AHUD> DefaultHUDFound(TEXT("/Game/TPE/Blueprints/UI/TPE_HUD.TPE_HUD_C"));

	if (DefaultHUDFound.Succeeded())
	{
		HUDClass = DefaultHUDFound.Class;
	}
	
	PlayerControllerClass = ATPE_PlayerController::StaticClass();
}