// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_Detect.h"
#include "TPE_AIController.h"
#include "TPE_Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("DETECT");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(ATPE_AIController::TargetKey, nullptr);

	auto ControllingPawn = Cast<ATPE_Character>(OwnerComp.GetAIOwner()->GetPawn());
	if (!ControllingPawn || ControllingPawn->IsDead()) { return; }

	auto World = ControllingPawn->GetWorld();
	auto Center = ControllingPawn->GetActorLocation();
	auto DetectRadius = 2000.0f;

	if (nullptr == World) { return; }
	
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	auto bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (0 < OverlapResults.Num())
	{
		for (auto OverlapResult : OverlapResults)
		{
			auto Character = Cast<ATPE_Character>(OverlapResult.GetActor());
			
			if (Character && Character->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ATPE_AIController::TargetKey, Character);

				OwnerComp.GetBlackboardComponent()->SetValueAsBool(ATPE_AIController::IsInBattleKey, true);

				DrawDebugPoint(World, Character->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), Character->GetActorLocation(), FColor::Blue, false, 2.0f);
				
				return;
			}
		}
	}
}