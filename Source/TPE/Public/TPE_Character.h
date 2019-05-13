// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPE.h"
#include "GameFramework/Character.h"
#include "TPE_Rotating.h"
#include "TPE_Character.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS(BlueprintType)
class TPE_API ATPE_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPE_Character();

	virtual void PostInitializeComponents() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Status")
		void Die();

	UFUNCTION(BlueprintCallable, Category = "Status")
		void Stun();

	UFUNCTION(BlueprintCallable, Category = "Status")
		bool IsDead() const { return bDead; }

	UFUNCTION(BlueprintCallable, Category = "Status")
		bool IsStunned() const { return bStunned; }

	UFUNCTION(BlueprintCallable, Category = "UI")
		UTPECharacterStatComponent* GetStatComponent() const { return CharacterStat; }

	UFUNCTION(BlueprintCallable, Category = "UI")
		class UWidgetComponent* GetWidgetComponent() const { return StatBarWidget; }

	UFUNCTION(BlueprintCallable, Category = "Equip")
		class ATPE_Weapon* GetRightWeapon() const { return RightWeapon; }

	UFUNCTION(BlueprintCallable, Category = "Equip")
		class ATPE_Weapon* GetLeftWeapon() const { return LeftWeapon; }

	UFUNCTION()
		class ATPE_Weapon* CreateWeapon(class UClass* Class);

	UFUNCTION()
		virtual void EquipWeapon(FName SocketName, class ATPE_Weapon* NewWeapon);

	UFUNCTION()
		virtual void UnEquipWeapon(class ATPE_Weapon* NewWeapon);

	UFUNCTION()
		void OnAttackMontageEnded(class UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Dash")
		void Dash();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Attack")
		void Attack();

	FOnAttackEndDelegate OnAttackEnd;

protected:

	UFUNCTION(BlueprintCallable, Category = "Equip")
		virtual void RightEquipWeapon(class ATPE_Weapon* Weapon);

	UFUNCTION(BlueprintCallable, Category = "Equip")
		virtual void LeftEquipWeapon(class ATPE_Weapon* Weapon);

	UFUNCTION(BlueprintCallable, Category = "Equip")
		virtual void RightUnEquipWeapon();

	UFUNCTION(BlueprintCallable, Category = "Equip")
		virtual void LeftUnEquipWeapon();

	UFUNCTION(BlueprintCallable, Category = "Equip")
		virtual void RightCreateWeaponAndEquip(class UClass* Class);

	UFUNCTION(BlueprintCallable, Category = "Equip")
		virtual void LeftCreateWeaponAndEquip(class UClass* Class);

	UFUNCTION(BlueprintCallable, Category = "Equip")
		FString GetSocketNameByWeaponType(int WeaponType);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		class UTPECharacterStatComponent* CharacterStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		class UTPE_AnimInstance* TPE_Anim;

	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* StatBarWidget;

	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* OnScreenControls;

	UPROPERTY(VisibleAnywhere, Category = "Equip")
		class ATPE_Weapon* RightWeapon;

	UPROPERTY(VisibleAnywhere, Category = "Equip")
		class ATPE_Weapon* LeftWeapon;

	bool bDead = false;

	bool bStunned = false;
};
