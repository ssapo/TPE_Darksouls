// Fill out your copyright notice in the Description page of Project Settings.


#include "TPE_AttackingAnimNotifyState.h"
#include "TPE_AnimInstance.h"

void UTPE_AttackingAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	auto TPEAnim = Cast<UTPE_AnimInstance>(MeshComp->GetAnimInstance());
	TPE_CHECK(TPEAnim);
	
	TPEAnim->SetCanInturuptAttacking(false);
}

void UTPE_AttackingAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	auto TPEAnim = Cast<UTPE_AnimInstance>(MeshComp->GetAnimInstance());
	TPE_CHECK(TPEAnim);
	
	TPEAnim->SetCanInturuptAttacking(true);
}