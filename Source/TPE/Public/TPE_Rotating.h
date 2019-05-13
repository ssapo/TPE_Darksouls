// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TPE_Rotating.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTPE_Rotating : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class TPE_API ITPE_Rotating
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Rotating")
		FRotator GetDesiredRotation() const;
};
