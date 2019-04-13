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

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetDeadAnim() { bIsDead = true; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	bool IsDead() const { return bIsDead; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetCanInturuptAttacking(bool NewValue) { bCanInturuptAttacking = NewValue; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	bool CanInturuptAttacking() const { return bCanInturuptAttacking; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetInAir(bool NewValue) { bIsInAir = NewValue; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	bool IsInAir() const { return bIsInAir; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetCanStopDash(bool NewValue) { bCanStopDash = NewValue; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	bool CanStopDash() const { return bCanStopDash; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetCanCombo(bool NewValue) { bCanCombo = NewValue; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	bool CanCombo() const { return bCanCombo; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetCanInturuptDash(bool NewValue) { bCanInturuptDash = NewValue; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	bool CanInturuptDash() const { return bCanInturuptDash; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	bool bIsInAir;

	bool bCanInturuptAttacking;

	bool bCanStopDash;
	
	bool bCanCombo;

	bool bIsDead;

	bool bCanInturuptDash;
};
