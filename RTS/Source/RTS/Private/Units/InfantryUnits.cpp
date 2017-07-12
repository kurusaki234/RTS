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

	SetHealth(InitialHealth);
	SetDamage(AttackDamage);
	SetAttackRange(AttackRange);

	bIsTargeting = false;
	bWantsToRun = false;
	bWantsToFire = false;
}

void AInfantryUnits::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SpawnDefaultHolster();
}

void AInfantryUnits::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!IsRunning())
	{
		SetRunning(false);
	}

	if (GEngine->UseSound())
	{
		UpdateRunSounds();
	}
}

void AInfantryUnits::Destroyed()
{
	Super::Destroyed();
	DestroyHolster();
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
			//bIsEnemy = DefaultGame->Can
		}
	}

	return bIsEnemy;
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
{
	if (!bWantsToFire)
	{
		bWantsToFire = true;

		if (CurrentWeapon)
		{
			CurrentWeapon->StartFire();
		}
	}
}

void AInfantryUnits::StopWeaponFire()
{
	if (bWantsToFire)
	{
		bWantsToFire = false;

		if (CurrentWeapon)
		{
			CurrentWeapon->StopFire();
		}
	}
}

bool AInfantryUnits::CanFire() const
{
	return IsAlive();
}

void AInfantryUnits::SetTargeting(bool bNewTargeting)
{
	bIsTargeting = bNewTargeting;
}

void AInfantryUnits::SetRunning(bool bNewRunning)
{
	bWantsToRun = bNewRunning;
}

float AInfantryUnits::PlayAnimMontage(UAnimMontage * AnimMontage, float InPlayRate, FName StartSectionName)
{
	USkeletalMeshComponent* UseMesh = GetPawnMesh();
	
	if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance)
	{
		return UseMesh->AnimScriptInstance->Montage_Play(AnimMontage, InPlayRate);
	}

	return 0.0f;
}

void AInfantryUnits::StopAnimMontage(UAnimMontage * AnimMontage)
{
	USkeletalMeshComponent* UseMesh = GetPawnMesh();

	if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance &&
		UseMesh->AnimScriptInstance->Montage_IsPlaying(AnimMontage))
	{
		UseMesh->AnimScriptInstance->Montage_Stop(AnimMontage->BlendOut.GetBlendTime(), AnimMontage);
	}
}

void AInfantryUnits::StopAllAnimMontages()
{
	USkeletalMeshComponent* UseMesh = GetPawnMesh();

	if (UseMesh && UseMesh->AnimScriptInstance)
	{
		UseMesh->AnimScriptInstance->Montage_Stop(0.0f);
	}
}

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

void AInfantryUnits::OnStartFire()
{
	ARTSPlayerController* MyPC = Cast<ARTSPlayerController>(Controller);

	if (MyPC)
	{
		if (IsRunning())
		{
			SetRunning(false);
		}
		StartWeaponFire();
	}
}

void AInfantryUnits::OnStopFire()
{
	StopWeaponFire();
}

void AInfantryUnits::OnStartTargeting()
{
	ARTSPlayerController* MyPC = Cast<ARTSPlayerController>(Controller);

	if (MyPC)
	{
		if (IsRunning())
		{
			SetRunning(false);
		}
		SetTargeting(true);
	}
}

void AInfantryUnits::OnStopTargeting()
{
	SetTargeting(false);
}

void AInfantryUnits::OnNextWeapon()
{
	ARTSPlayerController* MyPC = Cast<ARTSPlayerController>(Controller);

	if (MyPC)
	{
		if (Holster.Num() >= 2 && (CurrentWeapon == NULL || CurrentWeapon->GetCurrentStance() != ECurrentStance::Equipping))
		{
			const int32 CurrentWeaponIndex = Holster.IndexOfByKey(CurrentWeapon);
			AGunWeapon* NextWeapon = Holster[(CurrentWeaponIndex + 1) % Holster.Num()];
			EquipWeapon(NextWeapon);
		}
	}
}

void AInfantryUnits::OnPrevWeapon()
{
	ARTSPlayerController* MyPC = Cast<ARTSPlayerController>(Controller);

	if (MyPC)
	{
		if (Holster.Num() >= 2 && (CurrentWeapon == NULL || CurrentWeapon->GetCurrentStance() != ECurrentStance::Equipping))
		{
			const int32 CurrentWeaponIndex = Holster.IndexOfByKey(CurrentWeapon);
			AGunWeapon* PrevWeapon = Holster[(CurrentWeaponIndex - 1) % Holster.Num()];
			EquipWeapon(PrevWeapon);
		}
	}
}

void AInfantryUnits::OnStartRunning()
{
	ARTSPlayerController* MyPC = Cast<ARTSPlayerController>(Controller);

	if (MyPC)
	{
		if (IsTargeting())
		{
			SetTargeting(false);
		}
		StopWeaponFire();
		SetRunning(true);
	}
}

void AInfantryUnits::OnStopRunning()
{
	SetRunning(false);
}

USkeletalMeshComponent * AInfantryUnits::GetPawnMesh() const
{
	return GetMesh();
}

AGunWeapon * AInfantryUnits::GetWeapon() const
{
	return CurrentWeapon;
}

FName AInfantryUnits::GetWeaponAttachPoint() const
{
	return WeaponAttachPoint;
}

int32 AInfantryUnits::GetHolsterCount() const
{
	return Holster.Num();
}

AGunWeapon * AInfantryUnits::GetHolsterWeapon(int32 index) const
{
	return Holster[index];
}

bool AInfantryUnits::IsTargeting() const
{
	return bIsTargeting;
}

bool AInfantryUnits::IsFiring() const
{
	return bWantsToFire;
}

float AInfantryUnits::GetRunningSpeedModifier() const
{
	return RunningSpeedModifier;
}

float AInfantryUnits::GetTargetingSpeedModifier() const
{
	return TargetingSpeedModifier;
}

bool AInfantryUnits::IsRunning() const
{
	if (!GetCharacterMovement())
	{
		return false;
	}

	return bWantsToRun && !GetVelocity().IsZero() && (GetVelocity().GetSafeNormal2D() | GetActorForwardVector()) > -0.1;
}

int32 AInfantryUnits::GetHealth() const
{
	return health;
}

void AInfantryUnits::SetHealth(int32 value)
{
	health = value;
}

float AInfantryUnits::GetDamage() const
{
	return damage;
}

void AInfantryUnits::SetDamage(float value)
{
	damage = value;
}

float AInfantryUnits::GetAttackRange() const
{
	return attackRange;
}

void AInfantryUnits::SetAttackRange(float value)
{
	attackRange = value;
}

bool AInfantryUnits::IsAlive() const
{
	return health > 0;
}

void AInfantryUnits::UpdateRunSounds()
{
	const bool bIsRunSoundPlaying = RunLoopingAC != nullptr && RunLoopingAC->IsActive();
	const bool bWantsRunSoundPlaying = IsRunning() && IsMoving();

	if (!bIsRunSoundPlaying && bWantsRunSoundPlaying)
	{
		if (RunLoopingAC != nullptr)
		{
			RunLoopingAC->Play();
		}
		else if (RunLoopingSFX != nullptr)
		{
			RunLoopingAC = UGameplayStatics::SpawnSoundAttached(RunLoopingSFX, GetRootComponent());

			if (RunLoopingAC != nullptr)
			{
				RunLoopingAC->bAutoDestroy = false;
			}
		}
	}
	else if (bIsRunSoundPlaying && !bWantsRunSoundPlaying)
	{
		RunLoopingAC->Stop();

		if (RunStopSFX != nullptr)
		{
			UGameplayStatics::SpawnSoundAttached(RunStopSFX, GetRootComponent());
		}
	}
}

bool AInfantryUnits::IsMoving()
{
	return FMath::Abs(GetLastMovementInputVector().Size()) > 0.0f;
}

float AInfantryUnits::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	ARTSPlayerController* MyPC = Cast<ARTSPlayerController>(Controller);

	if (health <= 0)
	{
		return 0;
	}

	// Modify based on game rules.
	ARTSGameMode* const Game = GetWorld()->GetAuthGameMode <ARTSGameMode>();
	Damage = Game ? Game->ModifyDamage(Damage, this, DamageEvent, EventInstigator, DamageCauser) : 0.0f;

	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.0f)
	{
		health -= ActualDamage;

		if (GetHealth() <= 0)
		{
			Die(ActualDamage, DamageEvent, EventInstigator, DamageCauser);
		}
		else
		{
			PlayHit(ActualDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
		}

		MakeNoise(1.0f, EventInstigator ? EventInstigator->GetPawn() : this);
	}
	return ActualDamage;
}

void AInfantryUnits::Suicide()
{
	KilledBy(this);
}

void AInfantryUnits::KilledBy(APawn * EventInstigator)
{
	if (!bIsDying)
	{
		AController* Killer = NULL;

		if (EventInstigator != NULL)
		{
			Killer = EventInstigator->Controller;
			LastHitBy = NULL;
		}

		Die(GetHealth(), FDamageEvent(UDamageType::StaticClass()), Killer, NULL);
	}
}

bool AInfantryUnits::CanDie(float Damage, FDamageEvent const & DamageEvent, AController * Killer, AActor * DamageCauser) const
{
	if (bIsDying
		|| IsPendingKill()
		|| GetWorld()->GetAuthGameMode<ARTSGameMode>() == NULL
		|| GetWorld()->GetAuthGameMode<ARTSGameMode>()->GetMatchState() == MatchState::LeavingMap)
	{
		return false;
	}

	return true;
}

bool AInfantryUnits::Die(float Damage, FDamageEvent const& DamageEvent, AController * Killer, AActor * DamageCauser)
{
	if (!CanDie(Damage, DamageEvent, Killer, DamageCauser))
	{
		return false;
	}

	SetHealth((int32)FMath::Min(0, GetHealth()));

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : GetDefault<UDamageType>();

	Killer = GetDamageInstigator(Killer, *DamageType);

	AController* const KilledPlayed = (Controller != NULL) ? Controller : Cast<AController>(GetOwner());

	//GetWorld()->GetAuthGameMode<ARTSGameMode>()->Killed

	GetCharacterMovement()->ForceReplicationUpdate();	

	OnDeath(Damage, DamageEvent, Killer ? Killer->GetPawn() : NULL, DamageCauser);

	return true;
}

void AInfantryUnits::FellOutOfWorld(const UDamageType & DamageType)
{
	Die(GetHealth(), FDamageEvent(DamageType.GetClass()), NULL, NULL);
}

void AInfantryUnits::OnDeath(float Damage, FDamageEvent const & DamageEvent, APawn * InstigatingPOawn, AActor * DamageCauser)
{
	if (bIsDying)
	{
		return;
	}

	bTearOff = true;
	bIsDying = true;

	if (DeathSFX)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSFX, GetActorLocation());
	}

	// Remove all weapons
	DestroyHolster();

	DetachFromControllerPendingDestroy();

	StopAllAnimMontages();

	if (RunLoopingAC)
	{
		RunLoopingAC->Stop();
	}

	if (GetMesh())
	{
		static FName CollisionProfileName(TEXT("Ragdoll"));

		GetMesh()->SetCollisionProfileName(CollisionProfileName);
	}

	SetActorEnableCollision(true);

	// Death anim
	float DeathAnimDuration = PlayAnimMontage(DeathAnim);

	// Ragdoll
	if (DeathAnimDuration > 0.0f)
	{
		// Trigger ragdoll a little before the animation early so the character
		// doesn't blend back to its normal position.
		const float TriggerRagdollTime = DeathAnimDuration - 0.7f;

		// Enable blend physics so the bones are properly blending against the montage.
		GetMesh()->bBlendPhysics = true;

		// Use a local timer handle as we don't need to store it for later but we don't need to look for something to clear
		FTimerHandle TimerHandle;

		GetWorldTimerManager().SetTimer(TimerHandle, this, &AInfantryUnits::SetRagdollPhysics, FMath::Max(0.1f, TriggerRagdollTime), false);
	}
	else
	{
		SetRagdollPhysics();
	}

	// Disable collision on capsule
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
}

void AInfantryUnits::PlayHit(float DamageTaken, FDamageEvent const & DamageEvent, APawn * InstigatingPawn, AActor * DamageCauser)
{
	if (DamageTaken > 0.0f)
	{
		ApplyDamageMomentum(DamageTaken, DamageEvent, InstigatingPawn, DamageCauser);
	}
}

void AInfantryUnits::SetRagdollPhysics()
{
	bool bInRagdoll = false;

	if (IsPendingKill())
	{
		bInRagdoll = false;
	}
	else if (!GetMesh() || !GetMesh()->GetPhysicsAsset())
	{
		bInRagdoll = false;
	}
	else
	{
		// Initialize Physics / etc
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->WakeAllRigidBodies();
		GetMesh()->bBlendPhysics = true;

		bInRagdoll = true;
	}

	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->SetComponentTickEnabled(false);

	if (!bInRagdoll)
	{
		// Hide and set short lifespan
		TurnOff();
		SetActorHiddenInGame(true);
		SetLifeSpan(1.0f);
	}
	else
	{
		SetLifeSpan(5.0f);
	}
}

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

