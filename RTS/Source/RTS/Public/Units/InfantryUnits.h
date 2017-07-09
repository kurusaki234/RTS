// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "InfantryUnits.generated.h"

UENUM()
enum class ControllerType
{
	CT_Player	UMETA(DisplayName = "Player"),
	CT_Bot		UMETA(DisplayName = "Bot")
};

UCLASS()
class RTS_API AInfantryUnits : public ACharacter
{
	GENERATED_BODY()

private:
	// Sets default values for this character's properties
	AInfantryUnits();

	// Spawn holster, setup initial variables
	virtual void PostInitializeComponents() override;

	// Cleanup holster
	virtual void Destroyed() override;

	// Check if pawn is enemy or given controller
	bool IsEnemyFor(AController* FriendlyController) const;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
	virtual float PlayAnimMontage(UAnimMontage * AnimMontage, float InPlayRate, FName StartSectionName) override;

	// Stop anim montage
	virtual void StopAnimMontage(UAnimMontage * AnimMontage) override;

	// Stop playing all montages
	void StopAllAnimMontages();

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "BehaviorTree")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "Setup")
	ControllerType AIControllerType;

protected:
	// Infantry/Tank units switch to attack move
	void AttackMove();

	// Tank units switch to crush move
	void CrushMove();

	// Tank units switch to reverse move
	void ReverseMove();

	// Stops Infantry/Tank movement
	void Stop();

	// Infantry/Tank units switch to patrolling mode

};
