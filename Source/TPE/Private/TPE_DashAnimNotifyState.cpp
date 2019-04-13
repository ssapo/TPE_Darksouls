// Fill out your copyright notice in the Description page of Project Settings.


#include "TPE_DashAnimNotifyState.h"
#include "TPE_AnimInstance.h"

void UTPE_DashAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	auto TPEAnim = Cast<UTPE_AnimInstance>(MeshComp->GetAnimInstance());
	TPE_CHECK(TPEAnim);

	TPEAnim->SetCanStopDash(false);
}

void UTPE_DashAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	auto TPEAnim = Cast<UTPE_AnimInstance>(MeshComp->GetAnimInstance());
	TPE_CHECK(TPEAnim);

	TPEAnim->SetCanStopDash(true);
}
