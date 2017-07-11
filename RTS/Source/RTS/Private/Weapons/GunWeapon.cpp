// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "Weapons/GunWeapon.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AGunWeapon::AGunWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Root Component"));
	RootComponent = SceneComponent;

	Mesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh3P"));
	Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	Mesh->bReceivesDecals = false;
	Mesh->CastShadow = true;
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetupAttachment(SceneComponent);

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
{
	AttachMeshToPawn();

	bPendingEquip = true;
	DetermineCurrentStance();

	// Only play animation if last weapon is valid
	if (LastWeapon)
	{

	}
	else
	{
		OnEquipFinished();
	}

	if (MyPawn)
	{
		PlayWeaponSound(EquipSound);
	}
}

void AGunWeapon::OnEquipFinished()
{
	AttachMeshToPawn();

	bIsEquipped = true;
}

void AGunWeapon::OnUnEquip()
{}

void AGunWeapon::OnEnterHolster(AInfantryUnits * NewOwner)
{
	SetOwningPawn(NewOwner);
}

void AGunWeapon::OnLeaveHolster()
{
	SetOwningPawn(NULL);

	if (IsAttachedToPawn())
	{
		OnUnEquip();
	}
}

bool AGunWeapon::IsEquipped() const
{
	return bIsEquipped;
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
	bool bCanFire = MyPawn && MyPawn->CanFire();
	bool bStateOKToFire = ((CurrentStance == ECurrentStance::Idle) ||
		(CurrentStance == ECurrentStance::Firing));
	return ((bCanFire == true) && (bStateOKToFire == true));
}

ECurrentStance::Type AGunWeapon::GetCurrentStance() const
{
	return CurrentStance;
}

USkeletalMeshComponent * AGunWeapon::GetWeaponMesh() const
{
	return Mesh;
}

AInfantryUnits * AGunWeapon::GetPawnOwner() const
{
	return MyPawn;
}

void AGunWeapon::SetOwningPawn(AInfantryUnits* NewOwner)
{
	if (MyPawn != NewOwner)
	{
		MyPawn = NewOwner;

		SetOwner(NewOwner);
	}
}

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
{
	if (MyPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("AttachMeshToPawn"));
		FName AttachPoint = MyPawn->GetWeaponAttachPoint();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *AttachPoint.ToString());

		USkeletalMeshComponent* WeaponMesh = GetWeaponMesh();
		USkeletalMeshComponent* PawnMesh = MyPawn->GetPawnMesh();

		WeaponMesh->AttachToComponent(PawnMesh, FAttachmentTransformRules::KeepRelativeTransform,
			AttachPoint);


		UE_LOG(LogTemp, Warning, TEXT("%s"), *WeaponMesh->GetName());
		WeaponMesh->SetHiddenInGame(false);
	}
}

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
