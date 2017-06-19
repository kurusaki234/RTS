// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"		// Put new includes above

// Forward Declarations
class UTankBarrel; 
class UTankAimingComponent;

UCLASS()
class RTS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector hitLocation);

	UFUNCTION (BlueprintCallable, Category = "Setup")
	void SetBarrelReference(UTankBarrel* BarrelToSet);

protected:
	UTankAimingComponent* TankAimingComponent = nullptr; 

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float launchSpeed = 100000.0f;				// TODO find sensible defaut
};