// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPE.h"
#include "GameFramework/Character.h"
#include "TPE_Character.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS(BlueprintType)
class TPE_API ATPE_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPE_Character();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void OnAttackMontageEnded(class UAnimMontage* Montage, bool bInterrupted);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Status")
	void Die();

	UFUNCTION(BlueprintCallable, Category = "Status")
	bool IsDead() const { return bDead; }

	UFUNCTION()
	void SetStatbarWidgetVisibility(bool bFlag);

	UFUNCTION()
	virtual void EquipWeapon(FName SocketName, class ATPE_Weapon* NewWeapon);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Attack")
	void Attack();
	FOnAttackEndDelegate OnAttackEnd;

protected:
	UFUNCTION()
	virtual void RightEquipWeapon(class ATPE_Weapon* Weapon);

	UFUNCTION()
	virtual void LeftEquipWeapon(class ATPE_Weapon* Weapon);

private:
	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UTPECharacterStatComponent* CharacterStat;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
	class UTPE_AnimInstance* TPE_Anim;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* StatBarWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip", Meta = (AllowPrivateAccess = true))
	class ATPE_Weapon* RightWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip", Meta = (AllowPrivateAccess = true))
	class ATPE_Weapon* LeftWeapon;

	bool bDead = false;
};
