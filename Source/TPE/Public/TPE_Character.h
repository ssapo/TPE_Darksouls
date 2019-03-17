// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPE.h"
#include "GameFramework/Character.h"
#include "TPE_Attack.h"
#include "TPE_Character.generated.h"


UCLASS(BlueprintType)
class TPE_API ATPE_Character : public ACharacter, public ITPE_Attack
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPE_Character();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Attack")
	void Attack();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Attack")
	void AttackEnd();
	virtual void AttackEnd_Implementation() override;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UTPECharacterStatComponent* CharacterStat;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
	class UTPE_AnimInstance* TPE_Anim;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

};
