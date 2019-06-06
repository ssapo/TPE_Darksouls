// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPE.h"
#include "Containers/Map.h"
#include "TPE_Actor.h"
#include "TPE_Weapon.generated.h"

UCLASS()
class TPE_API ATPE_Weapon : public ATPE_Actor
{
	GENERATED_BODY()

public:
	ATPE_Weapon();

protected:
	virtual void BeginPlay() override;

private:

public:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void SetWeaponOwner(class ATPE_Character* NewWaeponOwner);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		class ATPE_Character* GetWeaponOwner() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		int GetType() const { return WeaponType; }

	UFUNCTION(BlueprintCallable, Category = "Weapon|Attack")
		void Attack();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Attack")
		void AttackEnd();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Attack")
		void BeginTrail();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Attack")
		void EndTrail();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Attack")
		void SetCollisionOn();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Attack")
		void SetCollisionOff();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Attack")
		void ResetAttackList();

protected:

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void InitWeapon(class UMeshComponent* NewWeaponBody, class UPrimitiveComponent* WeaponCollision, class UParticleSystemComponent* WeaponEffect);

	UFUNCTION(BlueprintNativeEvent)
		void OverlapBegin(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OverlapBegin_Implementation(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent)
		void OverlapEnd(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void OverlapEnd_Implementation(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private:

	UPROPERTY()
		class ATPE_Character* WeaponOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", Meta = (AllowPrivateAccess = true))
		class UPrimitiveComponent* WeaponCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", Meta = (AllowPrivateAccess = true))
		class UMeshComponent* WeaponBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", Meta = (AllowPrivateAccess = true))
		class UParticleSystemComponent* WeaponEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", Meta = (AllowPrivateAccess = true))
		int WeaponType = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Attack", Meta = (AllowPrivateAccess = true))
		float TrailInWidth = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Attack", Meta = (AllowPrivateAccess = true))
		float AttackDelayTime = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Attack", Meta = (AllowPrivateAccess = true))
		float AttackDamage = 30.0f;

	TMap<FString, TPair<bool, FTimerHandle>> AlreadyAttackList;
};
