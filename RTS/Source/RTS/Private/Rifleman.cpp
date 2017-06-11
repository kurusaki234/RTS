// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "Rifleman.h"


// Sets default values
ARifleman::ARifleman()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARifleman::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARifleman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARifleman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

