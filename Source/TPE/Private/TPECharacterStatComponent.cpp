// Fill out your copyright notice in the Description page of Project Settings.

#include "TPECharacterStatComponent.h"
#include "TPEGameInstance.h"

// Sets default values for this component's properties
UTPECharacterStatComponent::UTPECharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
}

// Called when the game starts
void UTPECharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}

void UTPECharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}

void UTPECharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto TPEGameInstance = Cast<UTPEGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	TPE_CHECK(nullptr != TPEGameInstance);
	CurrentStatData = TPEGameInstance->GetTPEChacracterData(NewLevel);
	if (nullptr != CurrentStatData)
	{
		Level = NewLevel;
		SetHP(CurrentStatData->MaxHP);
		SetStamina(CurrentStatData->MaxStamina);
	}
	else
	{
		TPE_LOG(Error, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}

void UTPECharacterStatComponent::SetDamage(int32 NewDamage)
{
	TPE_CHECK(nullptr != CurrentStatData);
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
}

void UTPECharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

void UTPECharacterStatComponent::SetStamina(float NewStamina)
{
	CurrentStamina = NewStamina;
	OnStaminaChanged.Broadcast();
	if (CurrentStamina < KINDA_SMALL_NUMBER)
	{
		CurrentStamina = 0.0f;
		OnStaminaIsZero.Broadcast();
	}
}

float UTPECharacterStatComponent::GetAttack() const
{
	TPE_CHECK(nullptr != CurrentStatData, 0.0f);
	return CurrentStatData->Attack;
}

float UTPECharacterStatComponent::GetHPRatio() const
{
	TPE_CHECK(nullptr != CurrentStatData, 0.0f);
	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
}

float UTPECharacterStatComponent::GetMaxHP() const
{
	TPE_CHECK(nullptr != CurrentStatData, 0.0f);
	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : CurrentStatData->MaxHP;
}

float UTPECharacterStatComponent::GetStaminaRatio() const
{
	TPE_CHECK(nullptr != CurrentStatData, 0.0f);
	return (CurrentStatData->MaxStamina < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentStamina / CurrentStatData->MaxStamina);
}

float UTPECharacterStatComponent::GetMaxStamina() const
{
	TPE_CHECK(nullptr != CurrentStatData, 0.0f);
	return (CurrentStatData->MaxStamina < KINDA_SMALL_NUMBER) ? 0.0f : CurrentStatData->MaxStamina;
}