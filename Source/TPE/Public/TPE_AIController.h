// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPE.h"
#include "AIController.h"
#include "TPE_AIController.generated.h"

/**
 * 
 */
UCLASS()
class TPE_API ATPE_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATPE_AIController();

	virtual void OnPossess(APawn* InPawn) override;

public:
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
	static const FName IsInBattleKey;

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
