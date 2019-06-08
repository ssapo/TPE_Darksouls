// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TPE_BlueprintFunctions.generated.h"

/**
 *
 */
UCLASS()
class TPE_API UTPE_BlueprintFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Library|Math")
		static float GetDistanceWithTwoVectors(const FVector& vec1, const FVector& vec2);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Library|Vector")
		static FVector GetZeroVector();

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Library|Float")
		static float GetFloatMin();

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Library|Float")
		static float GetFloatMax();

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Library|Int32")
		static int32 GetIntMin();

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Library|Int32")
		static int32 GetIntMax();

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Library|Transform")
		static FTransform GetTransformIdentity();


};
