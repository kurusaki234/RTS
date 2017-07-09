// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "GunWeapon.h"


// Sets default values
AGunWeapon::AGunWeapon (const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Mesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh3P"));
	Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	Mesh->bReceivesDecals = false;
	Mesh->CastShadow = true;
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	bLoopedMuzzleFX = false;
	bLoopedFireAnim = false;
	bPlayingFireAnim = false;
	bIsEquipped = false;
	bWantsToFire = false;
	bPendingEquip = false;
	CurrentStance = ECurrentStance::Idle;

	LastFireTime = 0.0f;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
}

void AGunWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AGunWeapon::Destroyed()
{
	Super::Destroyed();

	StopSimulatingWeaponFire();
}

void AGunWeapon::OnEquip(const AGunWeapon * LastWeapon)
{}

void AGunWeapon::OnEquipFinished()
{}

void AGunWeapon::OnUnEquip()
{}

bool AGunWeapon::IsEquipped() const
{
	return false;
}

bool AGunWeapon::IsAttachedToPawn() const
{
	return false;
}

void AGunWeapon::StartFire()
{}

void AGunWeapon::StopFire()
{}

bool AGunWeapon::CanFire() const
{
	return false;
}

ECurrentStance::Type AGunWeapon::GetCurrentStance() const
{
	return ECurrentStance::Type();
}

USkeletalMeshComponent * AGunWeapon::GetWeaponMesh() const
{
	return nullptr;
}

AInfantryUnits * AGunWeapon::GetPawnOwner() const
{
	return nullptr;
}

void AGunWeapon::SetOwningPawn(AInfantryUnits * AInfantryUnits)
{}

float AGunWeapon::GetEquipStartedTime() const
{
	return 0.0f;
}

float AGunWeapon::GetEquipDuration() const
{
	return 0.0f;
}

void AGunWeapon::SimulateWeaponFire()
{}

void AGunWeapon::StopSimulatingWeaponFire()
{}

void AGunWeapon::HandleFiring()
{}

void AGunWeapon::OnBurstStarted()
{}

void AGunWeapon::OnBurstFinished()
{}

void AGunWeapon::SetCurrentStance(ECurrentStance::Type NewStance)
{}

void AGunWeapon::DetermineCurrentStance()
{}

void AGunWeapon::AttachMeshToPawn()
{}

void AGunWeapon::DetachMeshFromPawn()
{}

UAudioComponent * AGunWeapon::PlayWeaponSound(USoundCue * Sound)
{
	return nullptr;
}

FVector AGunWeapon::GetMuzzleLocation() const
{
	return FVector();
}

FVector AGunWeapon::GetMuzzleDirection() const
{
	return FVector();
}

FHitResult AGunWeapon::WeaponTrace(const FVector & TraceFrom, const FVector & TraceTo) const
{
	return FHitResult();
}
