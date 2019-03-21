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
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called every frame
void ATPE_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

void ATPE_Character::AttackEnd_Implementation()
{
	OnAttackEnd.Broadcast();
	OnAttackEnd.Clear();
}

void ATPE_Character::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	AttackEnd_Implementation();
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

	//UWorld::SpawnActor<ATPE_Weapon>()

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
	EquipWeapon("socket_ik_hand_r", Weapon);
}

void ATPE_Character::LeftEquipWeapon(ATPE_Weapon* Weapon)
{
	EquipWeapon("socket_ik_hand_l", Weapon);
}
