// Fill out your copyright notice in the Description page of Project Settings.


#include "TPE_RotatingOwnerAnimNotifyState.h"
#include "TPE_RotatingComponent.h"

void UTPE_RotatingOwnerAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	auto RotatingComponent = Cast<UTPE_RotatingComponent>(MeshComp->GetOwner()->GetComponentByClass(UTPE_RotatingComponent::StaticClass()));
	if (RotatingComponent)
	{
		RotatingComponent->StartRotatingWithTime(TotalDuration, MaxDegreesPerSecond);
	}
}

void UTPE_RotatingOwnerAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	auto RotatingComponent = Cast<UTPE_RotatingComponent>(MeshComp->GetOwner()->GetComponentByClass(UTPE_RotatingComponent::StaticClass()));
	if (RotatingComponent)
	{
		RotatingComponent->StopRotating();
	}
}