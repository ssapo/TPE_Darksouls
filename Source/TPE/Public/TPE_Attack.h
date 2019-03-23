// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TPE_Attack.generated.h"

//DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTPE_Attack : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TPE_API ITPE_Attack
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//virtual void Attack() = 0;

	//FOnAttackEndDelegate OnAttackEnd;
};
