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

	DetachMeshFromPawn();
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
		float Duration = PlayWeaponAnimation(EquipAnim);

		if (Duration <= 0.0f)
		{
			// Failsafe
			Duration = 0.5f;
		}
		EquipStartedTime = GetWorld()->GetTimeSeconds();
		EquipDuration = Duration;

		GetWorldTimerManager().SetTimer(TimerHandle_OnEquipFinished, this,
			&AGunWeapon::OnEquipFinished, Duration, false);
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
	bPendingEquip = false;

	// Update the stance
	DetermineCurrentStance();
}

void AGunWeapon::OnUnEquip()
{
	DetachMeshFromPawn();
	bIsEquipped = false;
	StopFire();

	if (bPendingEquip)
	{
		StopWeaponAnimation(EquipAnim);
		bPendingEquip = false;

		GetWorldTimerManager().ClearTimer(TimerHandle_OnEquipFinished);
	}
	
	DetermineCurrentStance();
}

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
	return bIsEquipped || bPendingEquip;
}

void AGunWeapon::StartFire()
{
	if (!bWantsToFire)
	{
		bWantsToFire = true;
		DetermineCurrentStance();
	}
}

void AGunWeapon::StopFire()
{
	if (bWantsToFire)
	{
		bWantsToFire = false;
		DetermineCurrentStance();
	}
}

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
	return EquipStartedTime;
}

float AGunWeapon::GetEquipDuration() const
{
	return EquipDuration;
}

void AGunWeapon::SimulateWeaponFire()
{
	if (MuzzleFX)
	{
		USkeletalMeshComponent* UseWeaponMesh = GetWeaponMesh();

		if (!bLoopedMuzzleFX || MuzzlePSC == NULL)
		{
			if (MyPawn)
			{
				AController* PlayerController = MyPawn->GetController();

				if (PlayerController)
				{
					Mesh->GetSocketLocation(MuzzleAttachPoint);
					MuzzlePSC = UGameplayStatics::SpawnEmitterAttached(MuzzleFX, Mesh, MuzzleAttachPoint);
					MuzzlePSC->bOwnerNoSee = false;
					MuzzlePSC->bOnlyOwnerSee = false;
				}
			}
		}
	}

	if (!bLoopedFireAnim || !bPlayingFireAnim)
	{
		PlayWeaponAnimation(FireAnim);
		bPlayingFireAnim = true;
	}

	if (bLoopedFireSound)
	{
		if (FireAC == NULL)
		{
			FireAC = PlayWeaponSound(FireLoopSound);
		}
		else
		{
			PlayWeaponSound(FireSound);
		}
	}
}

void AGunWeapon::StopSimulatingWeaponFire()
{
	if (bLoopedMuzzleFX)
	{
		if (MuzzlePSC != NULL)
		{
			MuzzlePSC->DeactivateSystem();

			MuzzlePSC = NULL;
		}
	}

	if (bLoopedFireAnim && bPlayingFireAnim)
	{
		StopWeaponAnimation(FireAnim);
		bPlayingFireAnim = false;
	}

	if (FireAC)
	{
		FireAC->FadeOut(0.1f, 0.0f);
		FireAC = NULL;

		PlayWeaponSound(FireFinishSound);
	}
}

void AGunWeapon::HandleFiring()
{
	SimulateWeaponFire();

	if (MyPawn)
	{
		FireWeapon();

		bRefiring = (CurrentStance == ECurrentStance::Firing && WeaponConfig.TimeIntervals > 0.0f);

		if (bRefiring)
		{
			GetWorldTimerManager().SetTimer(TimerHandle_HandleFiring, this, &AGunWeapon::HandleFiring,
				WeaponConfig.TimeIntervals, false);
		}
	}

	LastFireTime = GetWorld()->GetTimeSeconds();
}

void AGunWeapon::OnBurstStarted()
{
	// Start firing, can be delayed to satisfy TimeBetweenShots
	const float GameTime = GetWorld()->GetTimeSeconds();

	if (LastFireTime > 0 && WeaponConfig.TimeIntervals > 0.0f &&
		LastFireTime + WeaponConfig.TimeIntervals > GameTime)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_HandleFiring, this,
			&AGunWeapon::HandleFiring, LastFireTime + WeaponConfig.TimeIntervals - GameTime, false);
	}
	else
	{
		HandleFiring();
	}
}

void AGunWeapon::OnBurstFinished()
{
	// Stop firing FX 
	BurstCounter = 0;

	StopSimulatingWeaponFire();

	GetWorldTimerManager().ClearTimer(TimerHandle_HandleFiring);
	bRefiring = false;
}

void AGunWeapon::SetCurrentStance(ECurrentStance::Type NewStance)
{
	const ECurrentStance::Type PrevStance = CurrentStance;

	if (PrevStance == ECurrentStance::Firing && NewStance != ECurrentStance::Firing)
	{
		OnBurstFinished();
	}

	CurrentStance = NewStance;

	if (PrevStance != ECurrentStance::Firing && NewStance == ECurrentStance::Firing)
	{
		OnBurstStarted();
	}
}

void AGunWeapon::DetermineCurrentStance()
{
	ECurrentStance::Type NewStance = ECurrentStance::Idle;

	if (bIsEquipped)
	{
		if (bWantsToFire)
		{
			NewStance = ECurrentStance::Firing;
		}
	}
	else if (bPendingEquip)
	{
		NewStance = ECurrentStance::Equipping;
	}

	SetCurrentStance(NewStance);
}

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

void AGunWeapon::DetachMeshFromPawn()
{
	Mesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	Mesh->SetHiddenInGame(true);
}

UAudioComponent * AGunWeapon::PlayWeaponSound(USoundCue * Sound)
{
	UAudioComponent* AC = NULL;

	if (Sound && MyPawn)
	{
		AC = UGameplayStatics::SpawnSoundAttached(Sound, MyPawn->GetRootComponent());
	}

	return AC;
}

float AGunWeapon::PlayWeaponAnimation(const FWeaponAnim & Animation)
{
	float Duration = 0.0f;

	if (MyPawn)
	{
		UAnimMontage* UseAnim = Animation.PawnAnim;

		if (UseAnim)
		{
			Duration = MyPawn->PlayAnimMontage(UseAnim);
		}
	}

	return Duration;
}

void AGunWeapon::StopWeaponAnimation(const FWeaponAnim & Animation)
{
	if (MyPawn)
	{
		UAnimMontage* UseAnim = Animation.PawnAnim;

		if (UseAnim)
		{
			MyPawn->StopAnimMontage(UseAnim);
		}
	}
}

FVector AGunWeapon::GetMuzzleLocation() const
{
	USkeletalMeshComponent* UseMesh = GetWeaponMesh();

	return UseMesh->GetSocketLocation("MuzzleAttachPoint");
}

FVector AGunWeapon::GetMuzzleDirection() const
{
	USkeletalMeshComponent* UseMesh = GetWeaponMesh();

	return UseMesh->GetSocketRotation("MuzzleAttachPoint").Vector();
}

FHitResult AGunWeapon::WeaponTrace(const FVector & TraceFrom, const FVector & TraceTo) const
{
	static FName WeaponFireTag = FName(TEXT("WeaponTrace"));

	// Perform trace to retrieve hit info
	FCollisionQueryParams TraceParams(WeaponFireTag, true, Instigator);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, TraceFrom, TraceTo, COLLISION_WEAPON, TraceParams);

	return Hit;
}
