// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hideCategories = ("Collision"))
class RTS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float relativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float maxDegreesPerSecond = 5.0f; // TODO Sensible default

	UPROPERTY(EditAnywhere, Category = "Setup")
	float maxElevationDegrees = 40.0f;	

	UPROPERTY(EditAnywhere, Category = "Setup")
	float minElevationDegrees = 0.0;
};
