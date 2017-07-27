// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "RTS_HUD.h"

ARTS_HUD::ARTS_HUD()
{
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(SphereRadius);

	EndLocation.Z += SphereHeight;
}

FVector2D ARTS_HUD::ConvertWorldLocationToLocal(AActor * Actor)
{
	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	if (Player && Actor)
	{
		// Convert the world location to local, based on the transform of the player
		FVector LocalVector = Player->GetTransform().InverseTransformPosition(Actor->GetActorLocation());

		// Rotate the vector by 90 degrees yaw anti-clockwise in order to have a valid rotation in our radar
		LocalVector = FRotator(0.0f, -90.0f, 0.0f).RotateVector(LocalVector);

		// Apply the given distance scale
		LocalVector /= RadarDistanceScale;

		// Return a 2D vector based on the 3D vector we've created above
		return FVector2D(LocalVector);
	}

	return FVector2D(0, 0);
}

void ARTS_HUD::DrawRaycastedActors()
{
	FVector2D RadarCenter = GetRadarCenterPosition();

	for (auto it : RadarActors)
	{
		FVector2D ConvertedLocation = ConvertWorldLocationToLocal(it);

		// We want to clamp the location of our actors in order to make sure that we display them inside our radar
		// To do so, we need a temporary vector in order to access the GetClampedToMaxSize2D function. This function
		// returns a clamped vector (if needed) to match our max length
		FVector tempVector = FVector(ConvertedLocation.X, ConvertedLocation.Y, 0.0f);

		// Subtract the pixel size in order to make the radar display more accurate
		tempVector = tempVector.GetClampedToMaxSize2D(SearchRadius - DrawPixelSize);

		// Assign the converted X and Y values to the vector we want to display
		ConvertedLocation.X = tempVector.X;
		ConvertedLocation.Y = tempVector.Y;

		DrawRect(FLinearColor::Red, RadarCenter.X + ConvertedLocation.X, RadarCenter.Y + ConvertedLocation.X, DrawPixelSize, DrawPixelSize);
	}
}

FVector2D ARTS_HUD::GetRadarCenterPosition()
{
	// If the canvas is valid, return the center as a 2D vector
	return (Canvas) ? FVector2D(Canvas->SizeX * StartLocation.X, Canvas->SizeY * StartLocation.Y) : FVector2D(0, 0);
}

void ARTS_HUD::DrawRadar()
{
	FVector2D RadarCenter = GetRadarCenterPosition();

	for (float i = 0; i < 360; i += DegreeStep)
	{
		// We want to draw a circle to represent our radar 
		// In order to do so, we calculate the sin and cos of almost every degree 
		// It is impossible to calculate each and every degree because they are infinite
		// lower the degree step in case you need a more accurate circle representation

		// We multiply our coordinates by radar size
		// In order to draw a circle with radius equal to the one we will input through the editor
		float fixedX = FMath::Cos(i) * SearchRadius;
		float fixedY = FMath::Sin(i) * SearchRadius;

		// Actual draw
		DrawLine(RadarCenter.X, RadarCenter.Y, RadarCenter.X + fixedX, RadarCenter.Y + fixedY, FLinearColor::Gray, 1.0f);
	}
}

void ARTS_HUD::DrawPlayer()
{
	FVector2D RadarCenter = GetRadarCenterPosition();

	DrawRect(FLinearColor::Black, RadarCenter.X, RadarCenter.Y, DrawPixelSize, DrawPixelSize);
}

void ARTS_HUD::PerformRadarRaycast()
{
	if (!Player)
	{
		Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}
	else
	{
		TArray <FHitResult> HitResults;

		EndLocation = Player->GetActorLocation();

		// Perform a necessary sweep for actors
		GetWorld()->SweepMultiByChannel
		(
			HitResults,
			Player->GetActorLocation(),
			EndLocation,
			FQuat::Identity,
			ECollisionChannel::ECC_WorldDynamic,
			CollisionShape
		);

		for (auto it : HitResults)
		{
			AActor* CurrentActor = it.GetActor();

			// In case the actor contains the word "Radar" as a tag, then add it into array
			if (CurrentActor && CurrentActor->ActorHasTag("Radar"))
				RadarActors.Add(CurrentActor);
		}
	}
}

void ARTS_HUD::DrawHUD()
{
	Super::DrawHUD();

	// Radar
	/*DrawRadar();

	DrawPlayer();

	PerformRadarRaycast();

	DrawRaycastedActors();

	// Empty the radar actors in case the player moves out of range, 
	// by doing so, we have always a valid display in our radar
	RadarActors.Empty();*/
}



