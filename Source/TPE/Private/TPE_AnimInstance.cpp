// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_AnimInstance.h"

void UTPE_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;

	if (!bIsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();

		static FVector2D InputRange(-180.0f, 180.0f);
		static FVector2D OutputRange(-50.0f, 50.0f);

		float Yaw = Pawn->GetControlRotation().Yaw - Pawn->GetActorRotation().Yaw;
		CurrentRotationRate = FMath::GetMappedRangeValueClamped(InputRange, OutputRange, Yaw);

		auto Character = Cast<ACharacter>(Pawn);
		if (Character) { bIsInAir = !Character->GetMovementComponent()->IsMovingOnGround(); }
	}
}



