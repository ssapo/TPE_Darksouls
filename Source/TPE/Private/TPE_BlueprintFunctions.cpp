// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_BlueprintFunctions.h"


FORCEINLINE float UTPE_BlueprintFunctions::GetDistanceWithTwoVectors(const FVector& vec1, const FVector& vec2)
{
	return (vec2 - vec1).Size();
}

FORCEINLINE FVector UTPE_BlueprintFunctions::GetZeroVector()
{
	return FVector::ZeroVector;
}

FORCEINLINE FTransform UTPE_BlueprintFunctions::GetTransformIdentity()
{
	return FTransform::Identity;
}