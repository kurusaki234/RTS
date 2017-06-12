// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "RTS_HUD.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ARTS_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ARTS_HUD();

protected:
	// The radar start locaiton
	UPROPERTY(EditAnywhere, Category = "Radar")
		FVector2D StartLocation = FVector2D(0.9f, 0.2f);

	// The radar radius
	UPROPERTY(EditAnywhere, Category = "Radar")
		float SearchRadius = 100.0;

	UPROPERTY(EditAnywhere, Category = "Radar")
		float DegreeStep = 0.25f;

	// The pixel size of the drawable actors
	UPROPERTY(EditAnywhere, Category = "Radar")
		float DrawPixelSize = 5.0f;

	// Sphere height and radius for our raycast
	UPROPERTY(EditAnywhere, Category = "Radar")
		float SphereHeight = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Radar")
		float SphereRadius = 3000.0f;

	// Holds a reference to every actor we are currently drawing in our radar
	TArray <AActor*> RadarActors;

	// The distance scale of the radar actor
	UPROPERTY(EditAnywhere, Category = "Radar")
		float RadarDistanceScale = 25.0f;

	// Converts the given actor's location to local (based on our character)
	FVector2D ConvertWorldLocationToLocal(AActor* Actor);


	// Draws the raycasted actors in our radar
	void DrawRaycastedActors();

	/*Sphere segments - used for visualization only*/
	UPROPERTY(EditAnywhere, Category = "Sweep")
		int32 Segments = 100;

	UPROPERTY()
	APawn* Player = nullptr;

	FCollisionShape CollisionShape;

	UPROPERTY()
	FVector EndLocation;

private:
	// Returns the center of the radar as a 2D Vector
	FVector2D GetRadarCenterPosition();

	// Draws the radar 
	void DrawRadar();
	
	void DrawPlayer();

	void PerformRadarRaycast();

	void DrawHUD();
};
