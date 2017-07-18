// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "InfantryUnits.generated.h"

UCLASS(Blueprintable, BlueprintType)
class RTS_API AInfantryUnits : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInfantryUnits();

	// Spawn holster, setup initial variables
	virtual void PostInitializeComponents() override;

	// Update the character
	virtual void Tick(float DeltaSeconds) override;

	// Cleanup holster
	virtual void Destroyed() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "BehaviorTree")
		class UBehaviorTree* BehaviorTree;

	/*UPROPERTY(EditAnywhere, Category = "Setup")
	ControllerType AIControllerType;*/

protected:
	// Check if pawn is enemy or given controller
	bool IsEnemyFor(AController* TargetController) const;

	// Add weapon to holster
	void AddWeapon(class AGunWeapon* Weapon);

	// Remove weapon from holster
	void RemoveWeapon(class AGunWeapon* Weapon);

	// Find in holster
	class AGunWeapon* FindWeapon(TSubclassOf<class AGunWeapon> WeaponClass);

	// Equips weapon from holster
	void EquipWeapon(class AGunWeapon* Weapon);

	//////////////////////////////////////////////////
	//					Weapon Usage				//
	//////////////////////////////////////////////////
	// Starts weapon fire
	void StartWeaponFire();

	// Stops weapon fire
	void StopWeaponFire();

public:
	// Check if the pawn can fire weapon
	bool CanFire() const;

	//////////////////////////////////////////////////
	//					Unit State					//
	//////////////////////////////////////////////////
	// Change targeting state 
	void SetTargeting(bool bNewTargeting);

	// Change running state
	void SetRunning(bool bNewRunning);

	//////////////////////////////////////////////////
	//					Animations					//
	//////////////////////////////////////////////////
	// Play anim montage
	virtual float PlayAnimMontage(class UAnimMontage * AnimMontage, float InPlayRate = 1.0f, FName StartSectionName = NAME_None) override;

	// Stop anim montage
	virtual void StopAnimMontage(class UAnimMontage * AnimMontage) override;

	// Stop playing all montages
	void StopAllAnimMontages();

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* DeathAnim;

	/////////////////////////////////////////////////////
	//					Basic Controls				   //
	/////////////////////////////////////////////////////

	// Infantry/Tank units switch to attack move
	void AttackMove();

	// Tank units switch to crush move
	void CrushMove();

	// Tank units switch to reverse move
	void ReverseMove();

	// Stops Infantry/Tank movement
	void Stop();

	// Infantry/Tank units switch to patrolling mode
	void Patrolling();

	// Infantry/Tank units force attacking the chosen target
	void ForceAttack();

	// Player pressed start fire action 
	void OnStartFire();

	// Player released start fire action 
	void OnStopFire();

	// Player pressed targeting action 
	void OnStartTargeting();

	// Player released targeting action 
	void OnStopTargeting();

	// Player pressed next weapon action 
	void OnNextWeapon();

	// Player pressed prev weapon action 
	void OnPrevWeapon();

	// Player pressed run action	
	void OnStartRunning();

	// Player released run action
	void OnStopRunning();


	/////////////////////////////////////////////////////////////
	//						Reading Data					   //
	/////////////////////////////////////////////////////////////
	// Get Skeletal Mesh Component
	USkeletalMeshComponent* GetPawnMesh() const;

	// Get Currently Equipped Weapon
	UFUNCTION(BlueprintCallable, Category = "Game | Weapon")
		class AGunWeapon* GetWeapon() const;

	// Get Weapon Attach Point
	FName GetWeaponAttachPoint() const;

	// Get Total Number of Holster Items 
	int32 GetHolsterCount() const;

	// Get Specific Weapon From Holster By Using Index
	class AGunWeapon* GetHolsterWeapon(int32 index) const;

	// Get Targeting State
	UFUNCTION(BlueprintCallable, Category = "Game | Weapon")
		bool IsTargeting() const;

	// Get Firing State
	UFUNCTION(BlueprintCallable, Category = "Game | Weapon")
		bool IsFiring() const;

	// Get The Modifier Value For Running Speed
	UFUNCTION(BlueprintCallable, Category = "Game | Weapon")
		float GetRunningSpeedModifier() const;

	UFUNCTION(BlueprintCallable, Category = "Game | Weapon")
		float GetTargetingSpeedModifier() const;

	// Get Running State
	UFUNCTION(BlueprintCallable, Category = "Pawn")
		bool IsRunning() const;

	// Get Max Health
	int32 GetHealth() const;

	// Set Health
	void SetHealth(int32 value);

	// Get Total Damage
	float GetDamage() const;

	// Set Total Damage
	void SetDamage(float value);

	// Get Attack Range
	float GetAttackRange() const;

	// Set Attack Range
	void SetAttackRange(float value);

	// Check if pawn is still alive
	bool IsAlive() const;

protected:
	// Socket or bone name for attaching weapon mesh
	UPROPERTY(EditDefaultsOnly, Category = "Holster")
		FName WeaponAttachPoint;

	// Default holster list
	UPROPERTY(EditDefaultsOnly, Category = "Holster")
		TArray<TSubclassOf <class AGunWeapon>> DefaultHolsterClasses;

	// Weapons in holster
	UPROPERTY(Transient)
		TArray<class AGunWeapon*> Holster;

	// Currently equipped weapon
	UPROPERTY(Transient)
		class AGunWeapon* CurrentWeapon;

	// Modifier for max movement speed
	UPROPERTY(EditDefaultsOnly, Category = "Pawn")
		float RunningSpeedModifier;

	UPROPERTY(EditDefaultsOnly, Category = "Pawn")
		float TargetingSpeedModifier;

	// Current Targeting State
	UPROPERTY(Transient)
		uint8 bIsTargeting : 1;

	// Current Running State
	UPROPERTY(Transient)
		uint8 bWantsToRun : 1;

	// Current Firing State
	UPROPERTY(Transient)
		uint8 bWantsToFire : 1;

	/////////////////////////////////////////////////////////////////
	//						Writting Data						   //
	/////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////
	//							Sound Effects					   //
	/////////////////////////////////////////////////////////////////
	// Death Sound Effect
	UPROPERTY(EditDefaultsOnly, Category = "Sound Effect")
		USoundCue* DeathSFX;

	// Run[Looping] Sound Effect
	UPROPERTY(EditDefaultsOnly, Category = "Sound Effect")
		USoundCue* RunLoopingSFX;

	// Run[Stop] Sound Effect
	UPROPERTY(EditDefaultsOnly, Category = "Sound Effect")
		USoundCue* RunStopSFX;

	// Hurt Sound Effect
	UPROPERTY(EditDefaultsOnly, Category = "Sound Effect")
		USoundCue* HurtSFX;

	// Audio Component used to manipulate with run loop sound
	UPROPERTY()
		UAudioComponent* RunLoopingAC;

	// Handles Sound For Running
	void UpdateRunSounds();

private:
	bool IsMoving();

public:
	///////////////////////////////////////////////////////////
	//						Damage & Death					 //
	///////////////////////////////////////////////////////////
	// Identifies if pawn is in its dying state
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
		uint32 bIsDying : 1;

	// Current health of the pawn 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		int32 InitialHealth;

	// Total damage of the pawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float AttackDamage;

	// Attack range of the pawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float AttackRange;

	// Take damage, handles death 
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, class AActor* DamageCauser) override;

	// Pawn Suicide
	virtual void Suicide();

	// Kill this pawn
	virtual void KilledBy(class APawn* EventInstigator);

	// Returns true if the pawn can die in the current state
	virtual bool CanDie(float Damage, FDamageEvent const& DamageEvent,
		AController* Killer, AActor* DamageCauser) const;

	// Kills pawn
	virtual bool Die(float Damage, FDamageEvent const& DamageEvent,
		AController* Killer, AActor* DamageCauser);

	// Die when pawn fall out of the world.
	virtual void FellOutOfWorld(const class UDamageType& DamageType) override;

protected:
	virtual void OnDeath(float Damage, struct FDamageEvent const& DamageEvent,
		class APawn* InstigatingPOawn, class AActor* DamageCauser);

	// Play effects On Hit
	virtual void PlayHit(float DamageTaken, struct FDamageEvent const& DamageEvent,
		class APawn* InstigatingPawn, class AActor* DamageCauser);

	// Switch to ragdoll
	void SetRagdollPhysics();

	////////////////////////////////////////////////////////////////
	//							Holster						      //
	////////////////////////////////////////////////////////////////
	// Updates Current Weapon
	void SetCurrentWeapon(class AGunWeapon* NewWeapon, class AGunWeapon* LastWeapon = NULL);

	// Spawn Default Holster
	void SpawnDefaultHolster();

	// Remove all weapons from holster and destroy them 
	void DestroyHolster();
private:
	int32 health;

	float movementSpeed;

	float damage;

	float attackRange;
};
