// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine/Engine.h"

DECLARE_LOG_CATEGORY_EXTERN(TPE, Log, All);

#define TPE_LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define TPE_LOG_S(Verbosity) UE_LOG(TPE, Verbosity, TEXT("%s"), *TPE_LOG_CALLINFO)
#define TPE_LOG(Verbosity, Format, ...) UE_LOG(TPE, Verbosity, TEXT("%s%s"), *TPE_LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define TPE_CHECK(Expr, ...) { if(!(Expr)) { TPE_LOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; } }

#define TPE_PRINT(Format, ...) { if(GEngine) { GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(Format, ##__VA_ARGS__), false, FVector2D::UnitVector); } }

#define TPE_PRINT_C(Color, Format, ...) { if(GEngine) { GEngine->AddOnScreenDebugMessage(-1, 3.0f, Color, FString::Printf(Format, ##__VA_ARGS__), false, FVector2D::UnitVector); } }

#define TPE_PRINT_CS(Color, Sec, Format, ...) { if(GEngine) { GEngine->AddOnScreenDebugMessage(-1, Sec, Color, FString::Printf(Format, ##__VA_ARGS__), false, FVector2D::UnitVector); } }