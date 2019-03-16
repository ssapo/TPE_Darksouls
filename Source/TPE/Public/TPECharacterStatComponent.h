// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPE.h"
#include "Components/ActorComponent.h"
#include "TPECharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate)
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate)

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
	void SetNewLevel(int32 NewLevel);

	void SetDamage(int32 NewDamage);

	void SetHP(float NewHP);

	float GetAttack() const;

	float GetHPRatio() const;


public:
	FOnHPIsZeroDelegate OnHPIsZero;

	FOnHPChangedDelegate OnHPChanged;

private:	
	struct FTPECharacterData* CurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentHP;
	
};
