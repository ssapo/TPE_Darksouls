// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetVisibleHP.h"
#include "TPE_AIController.h"
#include "TPE_Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Components/WidgetComponent.h"

UBTTask_SetVisibleHP::UBTTask_SetVisibleHP()
{
	NodeName = TEXT("SetVisibleHP");
}

EBTNodeResult::Type UBTTask_SetVisibleHP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	auto TPECharacter = Cast<ATPE_Character>(OwnerComp.GetAIOwner()->GetPawn());
	if (!TPECharacter) { return EBTNodeResult::Failed; }

	auto HPWidgetComponent = TPECharacter->GetWidgetComponent();
	if (!HPWidgetComponent) { return  EBTNodeResult::Failed; }

	HPWidgetComponent->SetVisibility(true);

	return EBTNodeResult::Succeeded;
}