// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPE.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "TPE_DashAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class TPE_API UTPE_DashAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) override;
};
