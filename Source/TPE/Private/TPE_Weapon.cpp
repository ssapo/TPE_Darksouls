// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_Weapon.h"
#include "Components/PrimitiveComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "TPE_Character.h"
//#include "GameFramework/AController.h"

// Sets default values
ATPE_Weapon::ATPE_Weapon()
{
	PrimaryActorTick.bCanEverTick = false;

	TrailInWidth = 1.5f;
	AttackDelayTime = 0.2f;
}

// Called when the game starts or when spawned
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
	if (false == WeaponCollision) { return; }

	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ATPE_Weapon::AttackEnd()
{
	if (false == WeaponCollision) { return; }

	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATPE_Weapon::BeginTrail()
{
	if (false == WeaponEffect) { return; }

	WeaponEffect->BeginTrails(TEXT("trail_socket_start"), TEXT("trail_socket_end"), ETrailWidthMode::ETrailWidthMode_FromCentre, TrailInWidth);
}

void ATPE_Weapon::EndTrail()
{
	if (false == WeaponEffect) { return; }

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

void ATPE_Weapon::OverlapBegin_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ATPE_Character::StaticClass()) && WeaponOwner != OtherActor)
	{
		auto OtherTPECharacter = Cast<ATPE_Character>(OtherActor);
		if (OtherTPECharacter)
		{
			if (!WeaponOwner->IsPlayerControlled() == !OtherTPECharacter->IsPlayerControlled()) { return; }

			if (!OtherTPECharacter->bCanBeDamaged) { return; }

			OtherTPECharacter->TakeDamage(30.0f, FDamageEvent(), WeaponOwner->GetController(), this);
			OtherTPECharacter->bCanBeDamaged = false;
		}
	}
	else if (OtherActor->IsA(ATPE_Actor::StaticClass()) && !OtherActor->IsA(ATPE_Weapon::StaticClass()))
	{
		if (!OtherActor->bCanBeDamaged) { return; }

		OtherActor->TakeDamage(30.0f, FDamageEvent(), WeaponOwner->GetController(), this);
		OtherActor->bCanBeDamaged = false;
	}
}

void ATPE_Weapon::OverlapEnd_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ATPE_Character::StaticClass()) && WeaponOwner != OtherActor)
	{
		auto OtherTPECharacter = Cast<ATPE_Character>(OtherActor);
		if (OtherTPECharacter)
		{
			if (!WeaponOwner->IsPlayerControlled() == !OtherTPECharacter->IsPlayerControlled()) { return; }

			if (OtherTPECharacter->bCanBeDamaged) { return; }
			
			FTimerHandle UnusedHandle;
			GetWorld()->GetTimerManager().SetTimer(UnusedHandle, [=]() {
				OtherActor->bCanBeDamaged = true;
			}, AttackDelayTime, false);
		}
	}
	else if (OtherActor->IsA(ATPE_Actor::StaticClass()) && !OtherActor->IsA(ATPE_Weapon::StaticClass()))
	{
		if (OtherActor->bCanBeDamaged) { return; }
		
		FTimerHandle UnusedHandle;
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, [=]() {
			OtherActor->bCanBeDamaged = true;
		}, AttackDelayTime, false);
	}

}


