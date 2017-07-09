// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "Units.h"


// Sets default values
AUnits::AUnits()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnits::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnits::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUnits::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

