// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	// TODO Should this really tick?

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!Barrel) { return; }

	FVector outLaunchVelocity;
	FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
							(
								this,
								outLaunchVelocity,
								startLocation,
								hitLocation,
								launchSpeed,
								false,
								0.0f,
								0.0f,
								ESuggestProjVelocityTraceOption::DoNotTrace
							);

	// Calculate the outLaunchVelocity
	if (bHaveAimSolution)
	{
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		auto time = GetWorld()->GetTimeSeconds();

		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), time);
		MoveBarrelTowards(aimDirection);
	}
	else
	{
		auto time = GetWorld()->GetTimeSeconds();

		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), time);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	// Find the current barrel rotation
	auto barrelRotator = Barrel->GetForwardVector().Rotation();
	
	// Convert FVector to rotation
	auto aimAsRotator = aimDirection.Rotation();

	auto deltaRotator = aimAsRotator - barrelRotator;


	Barrel->Elevate(deltaRotator.Pitch); // TODO remove magic number
}

