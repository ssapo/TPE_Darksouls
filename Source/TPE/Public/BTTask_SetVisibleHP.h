// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPE.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetVisibleHP.generated.h"

/**
 * 
 */
UCLASS()
class TPE_API UBTTask_SetVisibleHP : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SetVisibleHP();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
