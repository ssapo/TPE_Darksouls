// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPE.h"
#include "Components/ActorComponent.h"
#include "TPE_RotatingComponent.generated.h"

//DECLARE_MULTICAST_DELEGATE(FOnRotatingStart);
//DECLARE_MULTICAST_DELEGATE(FOnRotatingEnd);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPE_API UTPE_RotatingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTPE_RotatingComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

public:	
	void StartRotatingWithLimit(float NewMaxPossibleRotation, float NewMaxDegreesPerSecond);

	void StartRotatingWithTime(float NewTime, float NewMaxDegreesPerSecond);

	void StopRotating();

private:
	UPROPERTY(VisibleAnywhere)
	float TimeElapsed;

	UPROPERTY(VisibleAnywhere)
	float RotateTime;

	UPROPERTY(VisibleAnywhere)
	float MaxDegreesPerSecond;

	UPROPERTY(VisibleAnywhere)
	float MaxAllowedDegrees;

	UPROPERTY(VisibleAnywhere)
	bool bShouldRotate;
};
