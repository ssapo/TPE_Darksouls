// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_IsInAttackRange.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TPE_Character.h"
#include "TPE_AIController.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");

}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) { return false; }

	auto Target = Cast<ATPE_Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ATPE_AIController::TargetKey));
	if (nullptr == Target) { return false; }

	bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.0f);
	return bResult;
}