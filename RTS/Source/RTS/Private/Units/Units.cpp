// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "Units.h"
#include "Camera.h"
#include "FogOfWar.h"

// Sets default values
AUnits::AUnits()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bFogOfWar = false;
	bIsAlly = false;
	fogOfWarRadius = 0.0f;
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

	if (bIsAlly && bFogOfWar)
	{
		if (m_fow)
		{
			m_fow->revealSmoothCircle(FVector2D(GetActorLocation().X, GetActorLocation().Y), fogOfWarRadius);
		}
		else
		{
			if (m_fow == NULL)
			{
				for (TActorIterator<AFogOfWar> FogItr(GetWorld()); FogItr; ++FogItr)
				{
					m_fow = *FogItr;
				}
			}
		}
	}
}

// Called to bind functionality to input
void AUnits::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

