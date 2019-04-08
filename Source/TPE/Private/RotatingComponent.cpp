// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingComponent.h"

// Sets default values for this component's properties
URotatingComponent::URotatingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URotatingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void URotatingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

