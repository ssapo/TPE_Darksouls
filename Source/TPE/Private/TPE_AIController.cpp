// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TPE_Character.h"

const FName ATPE_AIController::HomePosKey(TEXT("HomePos"));
const FName ATPE_AIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ATPE_AIController::TargetKey(TEXT("Target"));

ATPE_AIController::ATPE_AIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBOject(TEXT("/Game/TPE/AI/BB_TPE_Character.BB_TPE_Character"));
	if (BBOject.Succeeded()) { BBAsset = BBOject.Object; }

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/TPE/AI/BT_TPE_Character.BT_TPE_Character"));
	if (BTObject.Succeeded()) { BTAsset = BTObject.Object; }
}

void ATPE_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			TPE_LOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}
}