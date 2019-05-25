// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPE.h"
#include "Components/ActorComponent.h"
#include "TPECharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHPDamagedDelegate, int32)
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate)
DECLARE_MULTICAST_DELEGATE(FOnStaminaZeroDelegate)
DECLARE_MULTICAST_DELEGATE(FOnStaminaChangedDelegate)
DECLARE_MULTICAST_DELEGATE(FOnStunBuildupZeroDelegate)
DECLARE_MULTICAST_DELEGATE(FOnStunBuildupChangedDelegate)

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TPE_API UTPECharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTPECharacterStatComponent();

protected:
	virtual void InitializeComponent() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = Stat)
		void SetNewLevel(int32 NewLevel);

	UFUNCTION(BlueprintCallable, Category = Stat)
		void SetDamage(int32 NewDamage);

	UFUNCTION(BlueprintCallable, Category = Stat)
		void SetHP(float NewHP, int32 HPDamaged);

	UFUNCTION(BlueprintCallable, Category = Stat)
		float GetHPRatio() const;

	UFUNCTION(BlueprintCallable, Category = Stat)
		float GetMaxHP() const;

	UFUNCTION(BlueprintCallable, Category = Stat)
		void AddStamina(float Value);

	UFUNCTION(BlueprintCallable, Category = Stat)
		void SubStamina(float Value);

	UFUNCTION(BlueprintCallable, Category = Stat)
		void SetStamina(float NewStamina);

	UFUNCTION(BlueprintCallable, Category = Stat)
		bool IsEnoughStamina(float CostStamina) const;

	UFUNCTION(BlueprintCallable, Category = Stat)
		float GetAttack() const;

	UFUNCTION(BlueprintCallable, Category = Stat)
		float GetStaminaRatio() const;

	UFUNCTION(BlueprintCallable, Category = Stat)
		float GetMaxStamina() const;

	UFUNCTION(BlueprintCallable, Category = Stat)
		void AddStunBuildup(float NewValue);

	UFUNCTION(BlueprintCallable, Category = Stat)
		void SubStunBuildup(float NewValue);

	UFUNCTION(BlueprintCallable, Category = Stat)
		void SetMaxStunBuildup();

	UFUNCTION(BlueprintCallable, Category = Stat)
		void SetStunBuildup(float NewValue);

	UFUNCTION(BlueprintCallable, Category = Stat)
		float GetMaxStunBuildup() const;

public:
	FOnHPIsZeroDelegate OnHPIsZero;

	FOnHPDamagedDelegate OnHPDamaged;

	FOnHPChangedDelegate OnHPChanged;

	FOnStaminaZeroDelegate OnStaminaIsZero;

	FOnStaminaChangedDelegate OnStaminaChanged;

	FOnStunBuildupZeroDelegate OnStunBuildIsZero;

	FOnStunBuildupChangedDelegate OnStunBuildupChanged;

private:
	struct FTPECharacterData* CurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 Level;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 Damaged;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentStamina;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentStunBuildup;
};
