// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "InfantryUnits.h"
#include "SpawnPoint.h"
#include "Camera.h"
#include "FogOfWar.h"

// Sets default values
ACamera::ACamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bFogOfWar = false;
}

// Called when the game starts or when spawned
void ACamera::BeginPlay()
{
	Super::BeginPlay();

	if (bFogOfWar)
	{
		m_fow = GetWorld()->SpawnActor<AFogOfWar>(AFogOfWar::StaticClass());

		m_fow->revealSmoothCircle(FVector2D(GetActorLocation().X, GetActorLocation().Y), 8000);
	}
}

// Called every frame
void ACamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    currentLevelName = GetLevel()->GetOuter()->GetName();
}

// Called to bind functionality to input
void ACamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


