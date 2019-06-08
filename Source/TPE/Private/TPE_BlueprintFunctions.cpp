// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_BlueprintFunctions.h"
#include "TPE.h"
#include "TPE_Math.h"

float UTPE_BlueprintFunctions::GetDistanceWithTwoVectors(const FVector& vec1, const FVector& vec2)
{
	return (vec2 - vec1).Size();
}

FVector UTPE_BlueprintFunctions::GetZeroVector()
{
	return FVector::ZeroVector;
}

FTransform UTPE_BlueprintFunctions::GetTransformIdentity()
{
	return FTransform::Identity;
}

float UTPE_BlueprintFunctions::GetFloatMin()
{
	return TNumericLimits<float>::Min();
}

float UTPE_BlueprintFunctions::GetFloatMax()
{
	return TNumericLimits<float>::Max();
}

int32 UTPE_BlueprintFunctions::GetIntMin()
{
	return TNumericLimits<int32>::Min();
}

int32 UTPE_BlueprintFunctions::GetIntMax()
{
	return TNumericLimits<int32>::Max();
}