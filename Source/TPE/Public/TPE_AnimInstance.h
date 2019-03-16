// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPE.h"
#include "Animation/AnimInstance.h"
#include "TPE_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TPE_API UTPE_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UTPE_AnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void SetDeadAnim() { IsDead = true; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDead;
};
