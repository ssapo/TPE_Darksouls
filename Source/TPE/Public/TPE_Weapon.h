// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPE.h"
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
	UFUNCTION(BlueprintCallable, Category = "Equip")
	void SetWeaponOwner(class ATPE_Character* NewWaeponOwner);
	
	UFUNCTION(BlueprintCallable, Category = "Equip")
	class ATPE_Character* GetWeaponOwner() const;

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void Attack();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AttackEnd();
	
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void BeginTrail();
	
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void EndTrail();

protected:

	UFUNCTION(BlueprintCallable, Category = "Equip")
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip", Meta = (AllowPrivateAccess = true))
	class UPrimitiveComponent* WeaponCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip", Meta = (AllowPrivateAccess = true))
	class UMeshComponent* WeaponBody;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equip", Meta = (AllowPrivateAccess = true))
	class UParticleSystemComponent* WeaponEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	float TrailInWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	float AttackDelayTime;

};
