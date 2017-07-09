// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SelectableUnits.generated.h"

UENUM()
enum class ControllerType
{
	CT_Player	UMETA(DisplayName = "Player"),
	CT_Bot		UMETA(DisplayName = "Bot")
};

UCLASS()
class RTS_API ASelectableUnits : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASelectableUnits();

	// Spawn holster, setup initial variables
	virtual void PostInitializeComponents() override;

	// Cleanup holster
	virtual void Destroyed() override;

	// Check if pawn is enemy or given controller
	bool IsEnemyFor(AController* FriendlyController) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "BehaviorTree")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "Setup")
	ControllerType AIControllerType;
};
