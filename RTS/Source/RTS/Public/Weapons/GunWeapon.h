// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GunWeapon.generated.h"

namespace ECurrentStance
{
	enum Type
	{
		Idle, 
		Firing, 
		Equipping,
	};
}

USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	/** Shooting time intervals */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Stat")
	float TimeIntervals;

	/** Constructor **/
	FWeaponData()
	{
		TimeIntervals = 0.55f;
	}
};

USTRUCT()
struct FWeaponAnim
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* PawnAnim;
};

UCLASS(Abstract, Blueprintable)
class RTS_API AGunWeapon : public AActor
{
	GENERATED_UCLASS_BODY()

	/** perform initial setup */
	virtual void PostInitializeComponents() override;

	virtual void Destroyed() override;

private:
	enum class EWeaponType
	{
		EAssaultRifle,
		ERocketLauncher,
		EFlameThrower,
		ESniper,
		EToolKit,
		EMax,
	};

	/** Query Ammo Type **/
	virtual EWeaponType GetWeaponType() const
	{
		return EWeaponType::EAssaultRifle;
	}

	/** Weapon is being equipped by owner pawn **/
	virtual void OnEquip(const AGunWeapon* LastWeapon);

	/** Weapon is now equipped by owner pawn **/
	virtual void OnEquipFinished();

	/** Weapon is holstered by owner pawn **/
	virtual void OnUnEquip();

	/** Check if it's currently equipped **/
	bool IsEquipped() const;

	/** Check if mesh is already attached **/
	bool IsAttachedToPawn() const;

	//////////////////////////////////////////////
	//					INPUT					//	
	//////////////////////////////////////////////

	/** Start Weapon Firing **/
	virtual void StartFire(); 
	
	/** Stop Weapon Firing **/
	virtual void StopFire();

	/** Check if weapon can fire **/
	bool CanFire() const;

	//////////////////////////////////////////////
	//			Getting Setup Properties		//
	//////////////////////////////////////////////

	/** Get current weapon state **/
	ECurrentStance::Type GetCurrentStance() const;

	/** Get Weapon Mesh (Needs pawn owner to determine variant) **/
	USkeletalMeshComponent* GetWeaponMesh() const;

	/** Get Pawn Owner **/
	UFUNCTION(BlueprintCallable, Category = "Game | Weapon")
	class AInfantryUnits* GetPawnOwner() const; 

	/** Set the weapon's owning pawn **/
	void SetOwningPawn(AInfantryUnits* InfantryUnits);

	/** Gets last time when this weapon was switched to **/
	float GetEquipStartedTime() const;

	/** Gets the duration of equipping weapon **/
	float GetEquipDuration() const;

protected:
	/** Pawn Owner **/
	UPROPERTY(Transient)
	class AInfantryUnits* MyPawn;

	/** Weapon Data **/
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	FWeaponData WeaponConfig;

private:
	/** Weapon Mesh **/
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* Mesh;

protected: 
	/** Name of bone / socket for muzzle in weapon mesh **/
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	FName MuzzleAttachPoint;

	/** Muzzle flash FX **/
	UParticleSystem* MuzzleFX;

	/** Spawned component for muzzle FX **/
	UPROPERTY(Transient)
	UParticleSystemComponent* MuzzlePSC;

	/** Firing audio (bLoopedFireSound set) **/
	UPROPERTY(Transient)
	UAudioComponent* FireAC;

	/** Single Fire Sound (bLoopedFireSound not set) **/
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* FireSound;

	/** Looped Fire Sound (bLoopedFireSound set) **/
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* FireLoopSound;

	/** Finished Burst Sound (bLoopedFireSound set) **/
	USoundCue* FireFinishSound;

	/** Equip Sound **/
	USoundCue* EquipSound;

	/** Equip Animations **/
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	FWeaponAnim EquipAnim;

	/** Fire Animation **/
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	FWeaponAnim FireAnim;

	/** Is Muzzle FX Looped? **/
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	uint32 bLoopedMuzzleFX : 1;

	/** Is Fire Sound Looped? **/
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	uint32 bLoopedFireSound : 1;

	/** Is Fire Animation Looped? **/
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	uint32 bLoopedFireAnim : 1;

	/** Is Fire Aniamtion Playing? **/
	uint32 bPlayingFireAnim : 1;

	/** Is Weapon Currently Equipped? **/
	uint32 bIsEquipped : 1;

	/** Is Weapon Fire Active? **/
	uint32 bWantsToFire : 1;

	/** Is Equip Animation Playing? **/
	uint32 bPendingEquip : 1;

	/** Weapon Is Refiring **/
	uint32 bRefiring;

	/** Current Stance **/
	ECurrentStance::Type CurrentStance;

	/** Time for last successful weapon fire **/
	float LastFireTime;

	/** Last time when this weapon was switched to **/
	float EquipStartedTime;

	/** How much time weapon needs to be equipped **/
	float EquipDuration;


	/** Handle for efficient management of OnEquipFinished timer **/
	FTimerHandle TimerHandle_OnEquipFinished; 

	/** Handle for efficient management of HandleFiring timer **/
	FTimerHandle TimerHandle_HandleFiring;


	/** Called in network play to do the cosmetic fx for firing */
	virtual void SimulateWeaponFire();

	/** Called in network play to stop cosmetic fx (e.g. for a looping shot). */
	virtual void StopSimulatingWeaponFire();

	////////////////////////////////////////////////
	//				Weapon Usage				 //
	///////////////////////////////////////////////
	virtual void FireWeapon() PURE_VIRTUAL(AGunWeapon::FireWeapon, );

	/** Handle Weapon Fire **/
	void HandleFiring();

	/** Firing Started **/
	virtual void OnBurstStarted();

	/** Firing Finished **/
	virtual void OnBurstFinished();

	/** Update Stance **/
	void SetCurrentStance(ECurrentStance::Type NewStance);

	/** Determine Current Stance **/
	void DetermineCurrentStance();

	//////////////////////////////////////////////////
	//					Inventory					//
	//////////////////////////////////////////////////
	
	/** Attaches weapon mesh to pawn's mesh **/
	void AttachMeshToPawn();

	/** Detaches weapon mesh from pawn **/
	void DetachMeshFromPawn();

	///////////////////////////////////////////////////
	//				Weapon Usage Helpers			 //
	///////////////////////////////////////////////////

	/** Play Weapon Sounds **/
	UAudioComponent* PlayWeaponSound(USoundCue* Sound);

	/** Get the muzzle location of the weapon **/
	FVector GetMuzzleLocation() const;

	/** Get Direction of Weapon's Muzzle **/
	FVector GetMuzzleDirection() const;
	
	/** Find Hit **/
	FHitResult WeaponTrace(const FVector& TraceFrom, const FVector& TraceTo) const;
protected:
	/** Returns Mesh subobject **/
	FORCEINLINE USkeletalMeshComponent* GetMesh() const { return Mesh; }
};
