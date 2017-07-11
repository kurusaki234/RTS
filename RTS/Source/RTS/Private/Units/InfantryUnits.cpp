// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "RTSPlayerState.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "InfantryUnits.h"
#include "Weapons/GunWeapon.h"

// Sets default values
AInfantryUnits::AInfantryUnits()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetMesh()->bReceivesDecals = false;
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	TargetingSpeedModifier = 0.5f;
	RunningSpeedModifier = 1.5f;

	bIsTargeting = false;
	bWantsToRun = false;
	bWantsToFire = false;
}

void AInfantryUnits::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InitialHealth = GetMaxHealth();
	SpawnDefaultHolster();
}

void AInfantryUnits::Destroyed()
{
	Super::Destroyed();


}

bool AInfantryUnits::IsEnemyFor(AController * TargetController) const
{
	if (TargetController == Controller || TargetController == NULL)
	{
		return false;
	}

	bool bIsEnemy = true;

	ARTSPlayerState* TargetPlayerState = Cast<ARTSPlayerState>(TargetController->PlayerState);
	ARTSPlayerState* OwnerPlayerState = Cast<ARTSPlayerState>(PlayerState);

	if (GetWorld()->GetGameState())
	{
		const ARTSGameMode* DefaultGame = GetWorld()->GetGameState()->GetDefaultGameMode<ARTSGameMode>();

		if (DefaultGame && OwnerPlayerState && TargetPlayerState)
		{
			//bIsEnemy = DefaultGame->
		}
	}

	return bIsEnemy;
}

// Called when the game starts or when spawned
void AInfantryUnits::BeginPlay()
{
	Super::BeginPlay();

}

void AInfantryUnits::AddWeapon(AGunWeapon * Weapon)
{
	if (Weapon)
	{
		Weapon->OnEnterHolster(this);
		Holster.AddUnique(Weapon);
	}
}

void AInfantryUnits::RemoveWeapon(AGunWeapon * Weapon)
{
	if (Weapon)
	{
		Weapon->OnLeaveHolster();
		Holster.RemoveSingle(Weapon);
	}
}

AGunWeapon * AInfantryUnits::FindWeapon(TSubclassOf<class AGunWeapon> WeaponClass)
{
	for (int32 i = 0; i < Holster.Num(); i++)
	{
		if (Holster[i] && Holster[i]->IsA(WeaponClass))
		{
			return Holster[i];
		}
	}

	return NULL;
}

void AInfantryUnits::EquipWeapon(AGunWeapon * Weapon)
{
	if (Weapon)
	{
		SetCurrentWeapon(Weapon, CurrentWeapon);
	}
}

void AInfantryUnits::StartWeaponFire()
{}

void AInfantryUnits::StopWeaponFire()
{}

bool AInfantryUnits::CanFire() const
{
	return IsAlive();
}

void AInfantryUnits::SetTargeting(bool bNewTargeting)
{
	bIsTargeting = bNewTargeting;
}

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

void AInfantryUnits::Patrolling()
{}

void AInfantryUnits::ForceAttack()
{}

USkeletalMeshComponent * AInfantryUnits::GetPawnMesh() const
{
	return GetMesh();
}

AGunWeapon * AInfantryUnits::GetWeapon() const
{
	return nullptr;
}

FName AInfantryUnits::GetWeaponAttachPoint() const
{
	return WeaponAttachPoint;
}

int32 AInfantryUnits::GetHolsterCount() const
{
	return int32();
}

AGunWeapon * AInfantryUnits::GetHolsterWeapon(int32 index) const
{
	return nullptr;
}

bool AInfantryUnits::IsFiring() const
{
	return false;
}

float AInfantryUnits::GetRunningSpeedModifier() const
{
	return RunningSpeedModifier;
}

float AInfantryUnits::GetTargetingSpeedModifier() const
{
	return TargetingSpeedModifier;
}

int32 AInfantryUnits::GetMaxHealth() const
{
	return GetClass()->GetDefaultObject<AInfantryUnits>()->InitialHealth;
}

bool AInfantryUnits::IsAlive() const
{
	return health > 0;
}

void AInfantryUnits::UpdateRunSounds()
{}

float AInfantryUnits::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	return 0.0f;
}

void AInfantryUnits::Suicide()
{}

void AInfantryUnits::KilledBy(APawn * EventInstigator)
{}

bool AInfantryUnits::CanDie(float Damage, FDamageEvent const & DamageEvent, AController * Killer, AActor * DamageCauser) const
{
	return false;
}

bool AInfantryUnits::Die(float Damage, FDamageEvent const & DamageEvent, AController * Killer, AActor * DamageCauser)
{
	return false;
}

void AInfantryUnits::FellOutOfWorld(const UDamageType & DamageType)
{}

void AInfantryUnits::PlayHit(float DamageTaken, FDamageEvent const & DamageEvent, APawn * InstigatingPawn, AActor * DamageCauser, bool bKilled)
{}

void AInfantryUnits::SetRagdollPhysics()
{}

void AInfantryUnits::SetCurrentWeapon(AGunWeapon* NewWeapon, AGunWeapon* LastWeapon)
{
	AGunWeapon* LocalLastWeapon = NULL;

	if (LastWeapon != NULL)
	{
		LocalLastWeapon = LastWeapon;
	}
	else if (NewWeapon != CurrentWeapon)
	{
		LocalLastWeapon = CurrentWeapon;
	}

	// Unequip previous
	if (LocalLastWeapon)
	{
		LocalLastWeapon->OnUnEquip();
	}

	CurrentWeapon = NewWeapon;

	// Equip new one
	if (NewWeapon)
	{
		NewWeapon->SetOwningPawn(this);
		NewWeapon->OnEquip(LastWeapon);
	}
}

void AInfantryUnits::SpawnDefaultHolster()
{
	int32 NumWeaponClasses = DefaultHolsterClasses.Num();

	for (int32 i = 0; i < NumWeaponClasses; i++)
	{
		if (DefaultHolsterClasses[i])
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AGunWeapon* NewWeapon = GetWorld()->SpawnActor<AGunWeapon>(DefaultHolsterClasses[i], SpawnInfo);
			AddWeapon(NewWeapon);
		}
	}

	// Equip first weapon in holster
	if (Holster.Num() > 0)
	{
		EquipWeapon(Holster[0]);
	}
}

void AInfantryUnits::DestroyHolster()
{
	for (int32 i = Holster.Num() - 1; i >= 0; i--)
	{
		AGunWeapon* Weapon = Holster[i];

		if (Weapon)
		{
			RemoveWeapon(Weapon);

			Weapon->Destroy();
		}
	}
}

