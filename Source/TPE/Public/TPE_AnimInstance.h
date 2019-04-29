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
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Montage")
	bool PlayMontageAttack();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Montage")
	bool StopMontageAttack();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Montage")
	bool PlayMontageDash();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Montage")
	bool StopMontageDash();

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	bool IsJumping() const { return IsInAir() || IsLanding(); }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetLanding(bool NewValue) { bLanding = NewValue; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	bool IsLanding() const { return bLanding; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void SetStunned(bool NewValue) { bStunned = NewValue; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	bool IsStunned() const { return bStunned; }

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
	float CurrentPawnSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentRotationRate = 0.0f;

	bool bLanding = true;

	bool bStunned = false;

	bool bIsInAir = false;

	bool bCanInturuptAttacking = true;

	bool bCanStopDash = true;
	
	bool bCanCombo = false;

	bool bIsDead = false;

	bool bCanInturuptDash = false;
};
