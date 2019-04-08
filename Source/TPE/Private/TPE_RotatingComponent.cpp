// Fill out your copyright notice in the Description page of Project Settings.


#include "TPE_RotatingComponent.h"
#include "GameFramework/Actor.h"
#include "TPE_Rotating.h"

UTPE_RotatingComponent::UTPE_RotatingComponent()
	: TimeElapsed(0.0f)
	, RotateTime(0.0f)
	, MaxDegreesPerSecond(0.0f)
	, MaxAllowedDegrees(0.0f)
	, bShouldRotate(false)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTPE_RotatingComponent::BeginPlay()
{
	Super::BeginPlay();
	
	TPE_CHECK(GetOwner()->Implements<UTPE_Rotating>());
}

void UTPE_RotatingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bShouldRotate) { return; }

	TimeElapsed += DeltaTime;

	if (TimeElapsed <= RotateTime)
	{
		auto NewRotation = FMath::RInterpConstantTo(
			GetOwner()->GetActorRotation(),
			ITPE_Rotating::Execute_GetDesiredRotation(GetOwner()),
			DeltaTime,
			MaxDegreesPerSecond
		);

		GetOwner()->SetActorRotation(NewRotation);
	}
	else
	{
		StopRotating();
	}
}

void UTPE_RotatingComponent::StartRotatingWithLimit(float NewMaxPossibleRotation, float NewMaxDegreesPerSecond)
{
	MaxDegreesPerSecond = NewMaxDegreesPerSecond;
	RotateTime = NewMaxPossibleRotation / MaxDegreesPerSecond;
	TimeElapsed = 0.0f;
	bShouldRotate = true;
}

void UTPE_RotatingComponent::StartRotatingWithTime(float NewTime, float NewMaxDegreesPerSecond)
{
	MaxDegreesPerSecond = NewMaxDegreesPerSecond;
	RotateTime = NewTime;
	TimeElapsed = 0.0f;
	bShouldRotate = true;
}

void UTPE_RotatingComponent::StopRotating() 
{
	bShouldRotate = false;
}