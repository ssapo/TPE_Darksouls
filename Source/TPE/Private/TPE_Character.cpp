// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_Character.h"
#include "TPECharacterStatComponent.h"
#include "TPE_AnimInstance.h"
#include "Components/WidgetCOmponent.h"
#include "TPE_CharacterWidget.h"
#include "TPE_AIController.h"
#include "TPE_Weapon.h"

// Sets default values
ATPE_Character::ATPE_Character()
{
	CharacterStat = CreateDefaultSubobject<UTPECharacterStatComponent>(TEXT("CHARACTERSTAT"));
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));

	HPBarWidget->SetupAttachment(GetMesh());

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/TPE/Blueprints/UI/UI_HPBar.UI_HPBar_C"));

	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.f, 50.0f));
	}

	AIControllerClass = ATPE_AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	 
	Dead = false;
}

// Called to bind functionality to input
void ATPE_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATPE_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	TPE_Anim = Cast<UTPE_AnimInstance>(GetMesh()->GetAnimInstance());
	TPE_CHECK(nullptr != TPE_Anim);

	TPE_Anim->OnMontageEnded.AddDynamic(this, &ATPE_Character::OnAttackMontageEnded);

	CharacterStat->SetNewLevel(IsPlayerControlled() ? 10 : 1);
	CharacterStat->OnHPIsZero.AddLambda([this]() -> void {
		TPE_LOG(Warning, TEXT("OHHPIsZero"));
		Die();
	});
}

float ATPE_Character::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	TPE_LOG(Warning, TEXT("Actor : %s took Damage %f"), *GetName(), FinalDamage);

	CharacterStat->SetDamage(FinalDamage);
	return FinalDamage;
}

void ATPE_Character::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	OnAttackEnd.Broadcast();
	OnAttackEnd.Clear();
}

// Called when the game starts or when spawned
void ATPE_Character::BeginPlay()
{
	Super::BeginPlay();

	auto CharacterWidget = Cast<UTPE_CharacterWidget>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != CharacterWidget)
	{
		CharacterWidget->BindCharacterStat(CharacterStat);
	}

	//ATPECharacter
	return;
	auto NewRightWeapon = GetWorld()->SpawnActor<ATPE_Weapon>(ATPE_Weapon::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	
	TPE_CHECK(nullptr != NewRightWeapon);
	RightEquipWeapon(NewRightWeapon);

	auto NewLeftWeapon = GetWorld()->SpawnActor<ATPE_Weapon>(ATPE_Weapon::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	
	TPE_CHECK(nullptr != NewLeftWeapon);
	LeftEquipWeapon(NewLeftWeapon);
}

void ATPE_Character::Die()
{
	TPE_CHECK(nullptr != TPE_Anim)

	Dead = true;
	TPE_Anim->SetDeadAnim();

	HPBarWidget->SetVisibility(false);
	SetActorEnableCollision(false);
}

void ATPE_Character::EquipWeapon(FName SocketName, ATPE_Weapon* Weapon)
{
	AttachToActor(Weapon, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), SocketName);
	Weapon->SetWeaponOwner(this);
}

void ATPE_Character::RightEquipWeapon(ATPE_Weapon* Weapon)
{
	TPE_PRINT(FColor::Red, TEXT("RightEquipWeapon"));
	EquipWeapon("socket_ik_hand_r", Weapon);
	RightWeapon = Weapon;
}

void ATPE_Character::LeftEquipWeapon(ATPE_Weapon* Weapon)
{
	TPE_PRINT(FColor::Red, TEXT("LeftEquipWeapon"));
	EquipWeapon("socket_ik_hand_l", Weapon);
	LeftWeapon = Weapon;
}
