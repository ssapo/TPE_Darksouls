// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_Character.h"
#include "TPECharacterStatComponent.h"
#include "TPE_AnimInstance.h"
#include "Components/WidgetComponent.h"
#include "TPE_CharacterWidget.h"
#include "TPE_AIController.h"
#include "TPE_Weapon.h"
#include "TPE_RotatingComponent.h"

ATPE_Character::ATPE_Character()
{
	CharacterStat = CreateDefaultSubobject<UTPECharacterStatComponent>(TEXT("CHARACTERSTAT"));
	StatBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("STATBARWIDGET"));
	OnScreenControls = CreateDefaultSubobject<UWidgetComponent>(TEXT("ONSCREENCONTROLS"));

	StatBarWidget->SetupAttachment(GetMesh());
	StatBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
	StatBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_STAT(TEXT("/Game/TPE/Blueprints/UI/UI_StatBar.UI_StatBar_C"));

	if (UI_STAT.Succeeded())
	{
		TPE_LOG(Warning, TEXT("Success UI_STAT"));

		StatBarWidget->SetWidgetClass(UI_STAT.Class);
		StatBarWidget->SetDrawSize(FVector2D(150.f, 12.5f));
		StatBarWidget->SetVisibility(false);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_ONSCREENCONTROLS(TEXT("/Game/TPE/Blueprints/UI/UI_PlayerOnScreenControls.UI_PlayerOnScreenControls_C"));

	if (UI_ONSCREENCONTROLS.Succeeded())
	{
		OnScreenControls->SetWidgetClass(UI_ONSCREENCONTROLS.Class);
		OnScreenControls->SetVisibility(false);
	}

	AIControllerClass = ATPE_AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bDead = false;
}

void ATPE_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	TPE_Anim = Cast<UTPE_AnimInstance>(GetMesh()->GetAnimInstance());
	TPE_CHECK(nullptr != TPE_Anim);

	TPE_Anim->OnMontageEnded.AddDynamic(this, &ATPE_Character::OnAttackMontageEnded);

	CharacterStat->OnStunBuildIsZero.AddUObject(this, &ATPE_Character::Stun);
	CharacterStat->OnHPIsZero.AddUObject(this, &ATPE_Character::Die);
}

float ATPE_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CharacterStat->SetDamage(FinalDamage);
	CharacterStat->SubStunBuildup(FinalDamage);
	return FinalDamage;
}

void ATPE_Character::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	OnAttackEnd.Broadcast();
	OnAttackEnd.Clear();
}

// Called when the game starts or when spawned
void ATPE_Character::BeginPlay()
{
	Super::BeginPlay();

	bool bPlayerControlled = IsPlayerControlled();

	if (bPlayerControlled)
	{
		if (nullptr != OnScreenControls)
		{
			auto UserWidget = OnScreenControls->GetUserWidgetObject();
			if (nullptr != UserWidget)
			{
				auto StatBar = Cast<UTPE_CharacterWidget>(UserWidget->GetWidgetFromName(TEXT("StatBar")));
				if (nullptr != StatBar)
				{
					UserWidget->AddToViewport();

					StatBar->BindCharacterStat(CharacterStat, true);
				}
			}
		}
	}
	else
	{
		auto CharacterWidget = Cast<UTPE_CharacterWidget>(StatBarWidget->GetUserWidgetObject());
		if (nullptr != CharacterWidget)
		{
			CharacterWidget->BindCharacterStat(CharacterStat, bPlayerControlled);
		}
	}
}

void ATPE_Character::Die()
{
	TPE_CHECK(nullptr != TPE_Anim);

	bDead = true;

	TPE_Anim->SetDeadAnim(true);
	SetActorEnableCollision(false);

	FTimerHandle UnusedHandle;
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, [this]() {
		StatBarWidget->SetVisibility(false);
		RightUnEquipWeapon();
		LeftUnEquipWeapon();
		}, 2.0f, false);
}

void ATPE_Character::Stun()
{
	TPE_CHECK(nullptr != TPE_Anim);
	TPE_CHECK(nullptr != CharacterStat);

	if (bStunned) { return; }

	bStunned = true;
	TPE_Anim->SetStunAnim(true);

	FTimerHandle UnusedHandle;
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, [this]() {
		TPE_Anim->SetStunAnim(false);
		bStunned = false;
		CharacterStat->SetMaxStunBuildup();
		}, 3.0f, false);
}

void ATPE_Character::UnEquipWeapon(ATPE_Weapon * Weapon)
{
	Weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	Weapon->SetWeaponOwner(nullptr);
}

void ATPE_Character::EquipWeapon(FName SocketName, ATPE_Weapon * Weapon)
{
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), SocketName);
	Weapon->SetWeaponOwner(this);
}

ATPE_Weapon* ATPE_Character::CreateWeapon(UClass * Class)
{
	return GetWorld()->SpawnActor<ATPE_Weapon>(Class);
}

void ATPE_Character::RightEquipWeapon(ATPE_Weapon * Weapon)
{
	EquipWeapon(TEXT("socket_ik_hand_r"), Weapon);
	RightWeapon = Weapon;
}

void ATPE_Character::LeftEquipWeapon(ATPE_Weapon * Weapon)
{
	EquipWeapon(TEXT("socket_ik_hand_l"), Weapon);
	LeftWeapon = Weapon;
}

void ATPE_Character::RightUnEquipWeapon()
{
	if (nullptr == RightWeapon) return;

	UnEquipWeapon(RightWeapon);
	RightWeapon = nullptr;
}

void ATPE_Character::LeftUnEquipWeapon()
{
	if (nullptr == LeftWeapon) return;

	UnEquipWeapon(LeftWeapon);
	LeftWeapon = nullptr;
}

void ATPE_Character::RightCreateWeaponAndEquip(UClass * Class)
{
	auto weapon = CreateWeapon(Class);
	if (weapon)
	{
		RightEquipWeapon(weapon);
	}
	else
	{
		TPE_PRINT(FColor::Green, TEXT("CreateWeapon is nullptr"));
	}
}

void ATPE_Character::LeftCreateWeaponAndEquip(UClass * Class)
{
	auto weapon = CreateWeapon(Class);
	if (weapon)
	{
		LeftEquipWeapon(weapon);
	}
	else
	{
		TPE_PRINT(FColor::Green, TEXT("CreateWeapon is nullptr"));
	}
}