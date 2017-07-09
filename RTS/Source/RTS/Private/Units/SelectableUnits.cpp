// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "SelectableUnits.h"

// Sets default values
ASelectableUnits::ASelectableUnits()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Ignore);
	

}

void ASelectableUnits::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ASelectableUnits::Destroyed()
{
}

bool ASelectableUnits::IsEnemyFor(AController * FriendlyController) const
{
	if (FriendlyController == Controller || FriendlyController == NULL)
	{
		return false;
	}

	bool bIsEnemy = true;

	/*if (GetWorld()->GetGameState())
	{
	//	const ART
	}*/
	return true;
}

// Called when the game starts or when spawned
void ASelectableUnits::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ASelectableUnits::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

