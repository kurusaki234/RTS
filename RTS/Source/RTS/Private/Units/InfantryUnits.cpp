// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "InfantryUnits.h"

// Sets default values
AInfantryUnits::AInfantryUnits()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Ignore);
}

void AInfantryUnits::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AInfantryUnits::Destroyed()
{
	Super::Destroyed();
}

bool AInfantryUnits::IsEnemyFor(AController * FriendlyController) const
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
void AInfantryUnits::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInfantryUnits::AddWeapon(AGunWeapon * Weapon)
{}

void AInfantryUnits::RemoveWeapon(AGunWeapon * Weapon)
{}

AGunWeapon * AInfantryUnits::FindWeapon(TSubclassOf<class AGunWeapon> WeaponClass)
{
	return nullptr;
}

void AInfantryUnits::EquipWeapon(AGunWeapon * Weapon)
{}

void AInfantryUnits::StartWeaponFire()
{}

void AInfantryUnits::StopWeaponFire()
{}

bool AInfantryUnits::CanFire() const
{
	return false;
}

void AInfantryUnits::SetTargeting(bool bNewTargeting)
{}

void AInfantryUnits::SetRunning(bool bNewRunning)
{}

float AInfantryUnits::PlayAnimMontage(UAnimMontage * AnimMontage, float InPlayRate, FName StartSectionName)
{
	return 0.0f;
}

void AInfantryUnits::StopAnimMontage(UAnimMontage * AnimMontage)
{}

void AInfantryUnits::StopAllAnimMontages()
{}

// Called to bind functionality to input
void AInfantryUnits::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AInfantryUnits::AttackMove()
{}

void AInfantryUnits::CrushMove()
{}

void AInfantryUnits::ReverseMove()
{}

void AInfantryUnits::Stop()
{}

