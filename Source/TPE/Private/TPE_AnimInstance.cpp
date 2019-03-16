// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_AnimInstance.h"

UTPE_AnimInstance::UTPE_AnimInstance()
{
	CurrentPawnSpeed = 0.0f;

	IsDead = false;
}

void UTPE_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;

	if (!IsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();

		auto Character = Cast<ACharacter>(Pawn);
		if (Character) { IsInAir = Character->GetMovementComponent()->IsFalling(); }
	}
}



