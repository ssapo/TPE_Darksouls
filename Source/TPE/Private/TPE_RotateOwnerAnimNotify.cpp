// Fill out your copyright notice in the Description page of Project Settings.


#include "TPE_RotateOwnerAnimNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequenceBase.h"
#include "TPE_RotatingComponent.h"

void UTPE_RotateOwnerAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	auto RotatingComponent = Cast<UTPE_RotatingComponent>(MeshComp->GetOwner()->GetComponentByClass(UTPE_RotatingComponent::StaticClass()));
	if (RotatingComponent)
	{ 
		RotatingComponent->StartRotatingWithLimit(MaxPossibleRotation, MaxDegreesPerSecond);
	}
}