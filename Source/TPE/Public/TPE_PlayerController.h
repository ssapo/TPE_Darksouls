// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPE_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TPE_API ATPE_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATPE_PlayerController();

	virtual void BeginPlay() override;
	virtual void Possess(APawn* InPawn) override; 
	virtual void UnPossess() override;

private:
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* OnScreenControls;
};
