// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Turn.h"
#include "TPE_AIController.h"
#include "TPE_Character.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_Turn::UBTTask_Turn()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_Turn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Character = Cast<ATPE_Character>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Character || true == Character->IsDead()) { return EBTNodeResult::Failed; }

	auto Target = Cast<ATPE_Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ATPE_AIController::TargetKey));
	if (nullptr == Target) { return EBTNodeResult::Failed; }

	FVector LookVector = Target->GetActorLocation() - Character->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	Character->SetActorRotation(FMath::RInterpTo(Character->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}
