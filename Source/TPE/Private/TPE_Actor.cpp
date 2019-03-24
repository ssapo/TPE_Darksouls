// Fill out your copyright notice in the Description page of Project Settings.

#include "TPE_Actor.h"

// Sets default values
ATPE_Actor::ATPE_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATPE_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPE_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

