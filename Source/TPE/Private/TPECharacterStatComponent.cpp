// Fill out your copyright notice in the Description page of Project Settings.

#include "TPECharacterStatComponent.h"
#include "TPEGameInstance.h"

// Sets default values for this component's properties
UTPECharacterStatComponent::UTPECharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	Level = 1;
}

void UTPECharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}


void UTPECharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AddStamina(10.0f * DeltaTime);
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
		SetStunBuildup(CurrentStatData->MaxStun);
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

void UTPECharacterStatComponent::AddStamina(float Value)
{
	TPE_CHECK(nullptr != CurrentStatData);
	SetStamina(FMath::Clamp<float>(CurrentStamina + Value, 0.0f, CurrentStatData->MaxStamina));
}

void UTPECharacterStatComponent::SubStamina(float Value)
{
	TPE_CHECK(nullptr != CurrentStatData);
	SetStamina(FMath::Clamp<float>(CurrentStamina - Value, 0.0f, CurrentStatData->MaxStamina));
}

void UTPECharacterStatComponent::AddStunBuildup(float Value)
{
	TPE_CHECK(nullptr != CurrentStatData);
	SetStunBuildup(FMath::Clamp<float>(CurrentStunBuildup + Value, 0.0f, CurrentStatData->MaxStun));
}

void UTPECharacterStatComponent::SubStunBuildup(float Value)
{
	TPE_CHECK(nullptr != CurrentStatData);
	SetStunBuildup(FMath::Clamp<float>(CurrentStunBuildup - Value, 0.0f, CurrentStatData->MaxStun));
}

void UTPECharacterStatComponent::SetMaxStunBuildup()
{
	TPE_CHECK(nullptr != CurrentStatData);
	SetStunBuildup(CurrentStatData->MaxStun);
}

void UTPECharacterStatComponent::SetHP(float NewValue)
{
	CurrentHP = NewValue;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

void UTPECharacterStatComponent::SetStamina(float NewValue)
{
	CurrentStamina = NewValue;
	OnStaminaChanged.Broadcast();
	if (CurrentStamina < KINDA_SMALL_NUMBER)
	{
		CurrentStamina = 0.0f;
		OnStaminaIsZero.Broadcast();
	}
}

void UTPECharacterStatComponent::SetStunBuildup(float NewValue)
{
	CurrentStunBuildup = NewValue;
	OnStunBuildupChanged.Broadcast();
	if (CurrentStunBuildup < KINDA_SMALL_NUMBER)
	{
		CurrentStunBuildup = 0.0f;
		OnStunBuildIsZero.Broadcast();
	}
}

bool UTPECharacterStatComponent::IsEnoughStamina(float CostStamina) const
{
	return CurrentStamina >= CostStamina;
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

float UTPECharacterStatComponent::GetMaxStunBuildup() const
{
	TPE_CHECK(nullptr != CurrentStatData, 0.0f);
	return (CurrentStatData->MaxStun < KINDA_SMALL_NUMBER) ? 0.0f : CurrentStatData->MaxStun;
}