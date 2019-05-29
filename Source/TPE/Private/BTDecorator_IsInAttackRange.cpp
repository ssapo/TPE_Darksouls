// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_IsInAttackRange.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TPE_Character.h"
#include "TPE_AIController.h"
#include "TPE_Math.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");

}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingCharacter = Cast<ATPE_Character>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingCharacter || true == ControllingCharacter->IsDead()) { return false; }

	auto Target = Cast<ATPE_Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ATPE_AIController::TargetKey));
	if (nullptr == Target) { return false; }

	auto Dist = Target->GetDistanceTo(ControllingCharacter);
	bResult = UKismetMathLibrary::InRange_FloatFloat(Dist, MinAttackRange, MaxAttackRange, true, true);
	return bResult;
}