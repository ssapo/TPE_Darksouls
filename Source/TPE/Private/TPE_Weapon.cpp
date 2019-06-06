// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_Weapon.h"
#include "Components/PrimitiveComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "TPE_Character.h"
//#include "GameFramework/AController.h"

ATPE_Weapon::ATPE_Weapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATPE_Weapon::BeginPlay()
{
	Super::BeginPlay();

	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &ATPE_Weapon::OverlapBegin);
	WeaponCollision->OnComponentEndOverlap.AddDynamic(this, &ATPE_Weapon::OverlapEnd);
}

void ATPE_Weapon::SetWeaponOwner(ATPE_Character* NewWaeponOwner)
{
	WeaponOwner = NewWaeponOwner;
}

ATPE_Character* ATPE_Weapon::GetWeaponOwner() const
{
	return WeaponOwner;
}

void ATPE_Weapon::Attack()
{
	SetCollisionOn();
}

void ATPE_Weapon::AttackEnd()
{
	SetCollisionOff();
	ResetAttackList();
}

void ATPE_Weapon::SetCollisionOn()
{
	if (nullptr == WeaponCollision) { return; }
	
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ATPE_Weapon::SetCollisionOff()
{
	if (nullptr == WeaponCollision) { return; }

	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATPE_Weapon::ResetAttackList()
{
	for (auto& e : AlreadyAttackList)
	{
		auto& Pair = e.Value;

		Pair.Key = false;
		GetWorld()->GetTimerManager().ClearTimer(Pair.Value);
	}
}

void ATPE_Weapon::BeginTrail()
{
	if (false == WeaponEffect) 
	{ 
		TPE_PRINT(TEXT("WeaponEffect is nullptr"));
		return; 
	}

	WeaponEffect->BeginTrails(TEXT("trail_socket_start"), TEXT("trail_socket_end"), ETrailWidthMode::ETrailWidthMode_FromCentre, TrailInWidth);
}

void ATPE_Weapon::EndTrail()
{
	if (false == WeaponEffect) 
	{
		TPE_PRINT(TEXT("WeaponEffect is nullptr"));
		return;
	}

	WeaponEffect->EndTrails();
}

void ATPE_Weapon::InitWeapon(UMeshComponent* NewWeaponBody, UPrimitiveComponent* NewWeaponCollision, UParticleSystemComponent* NewWeaponEffect)
{
	TPE_CHECK(nullptr != NewWeaponBody);
	TPE_CHECK(nullptr != NewWeaponCollision);
	TPE_CHECK(nullptr != NewWeaponEffect);

	WeaponBody = NewWeaponBody;
	WeaponCollision = NewWeaponCollision;
	WeaponEffect = NewWeaponEffect;
}

void ATPE_Weapon::OverlapBegin_Implementation(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(ATPE_Character::StaticClass()) && WeaponOwner != OtherActor)
	{
		auto OtherTPECharacter = Cast<ATPE_Character>(OtherActor);
		if (OtherTPECharacter)
		{
			if (!WeaponOwner->IsPlayerControlled() == !OtherTPECharacter->IsPlayerControlled()) { return; }

			auto& Finder = AlreadyAttackList.FindOrAdd(OtherActor);
			if (false == Finder.Key)
			{
				TPE_PRINT_CS(FColor::Green, 1.0f, TEXT("%s Damage: %f"), *OtherComp->GetName(), AttackDamage);
				OtherTPECharacter->TakeDamage(AttackDamage, FDamageEvent(), WeaponOwner->GetController(), this);
				Finder.Key = true;
			}
		}
	}
	else if (OtherActor->IsA(ATPE_Actor::StaticClass()) && !OtherActor->IsA(ATPE_Weapon::StaticClass()))
	{
		if (false == OtherActor->bCanBeDamaged) { return; }

		auto& Finder = AlreadyAttackList.FindOrAdd(OtherActor);
		if (false == Finder.Key)
		{
			OtherActor->TakeDamage(AttackDamage, FDamageEvent(), WeaponOwner->GetController(), this);
			Finder.Key = true;
		}
	}
}

void ATPE_Weapon::OverlapEnd_Implementation(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ATPE_Character::StaticClass()) && WeaponOwner != OtherActor)
	{
		auto OtherTPECharacter = Cast<ATPE_Character>(OtherActor);
		if (OtherTPECharacter)
		{
			if (!WeaponOwner->IsPlayerControlled() == !OtherTPECharacter->IsPlayerControlled()) { return; }

			auto& Finder = AlreadyAttackList.FindOrAdd(OtherActor);
			if (true == Finder.Key)
			{
				GetWorld()->GetTimerManager().SetTimer(Finder.Value, [=, &Finder]() {
					GetWorld()->GetTimerManager().ClearTimer(Finder.Value);
					Finder.Key = false;
					}, AttackDelayTime, false);
			}
		}
	}
	else if (OtherActor->IsA(ATPE_Actor::StaticClass()) && !OtherActor->IsA(ATPE_Weapon::StaticClass()))
	{
		auto& Finder = AlreadyAttackList.FindOrAdd(OtherActor);
		if (true == Finder.Key)
		{
			GetWorld()->GetTimerManager().SetTimer(Finder.Value, [=, &Finder]() {
				GetWorld()->GetTimerManager().ClearTimer(Finder.Value);
				Finder.Key = false;
				}, AttackDelayTime, false);
		}
	}

}


