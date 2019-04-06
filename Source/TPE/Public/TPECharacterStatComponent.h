// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPE.h"
#include "Components/ActorComponent.h"
#include "TPECharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate)
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate)
DECLARE_MULTICAST_DELEGATE(FOnStaminaZeroDelegate)
DECLARE_MULTICAST_DELEGATE(FOnStaminaChangedDelegate)


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TPE_API UTPECharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTPECharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

public:
	UFUNCTION(BlueprintCallable, Category = Stat)
	void SetNewLevel(int32 NewLevel);
	
	UFUNCTION(BlueprintCallable, Category = Stat)
	void SetDamage(int32 NewDamage);

	UFUNCTION(BlueprintCallable, Category = Stat)
	void SetHP(float NewHP);

	UFUNCTION(BlueprintCallable, Category = Stat)
	void SetStamina(float NewStamina);

	UFUNCTION(BlueprintCallable, Category = Stat)
	float GetAttack() const;

	UFUNCTION(BlueprintCallable, Category = Stat)
	float GetHPRatio() const;

	UFUNCTION(BlueprintCallable, Category = Stat)
	float GetMaxHP() const;

	UFUNCTION(BlueprintCallable, Category = Stat)
	float GetStaminaRatio() const;

	UFUNCTION(BlueprintCallable, Category = Stat)
	float GetMaxStamina() const;

public:
	FOnHPIsZeroDelegate OnHPIsZero;

	FOnHPChangedDelegate OnHPChanged;

	FOnStaminaZeroDelegate OnStaminaIsZero;

	FOnStaminaChangedDelegate OnStaminaChanged;

private:	
	struct FTPECharacterData* CurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentStamina;
};
