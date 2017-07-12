// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "StaticFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API UStaticFunctionLibrary : public UObject
{
	GENERATED_BODY()

public:
	static FORCEINLINE bool Trace(UWorld* world, TArray<AActor*>& ActorsToIgnore, const FVector& Start,
		const FVector& End, FHitResult& HitOut, ECollisionChannel CollisionChannel = ECC_Pawn, bool ReturnPhysMat = false)
	{
		if (!world)
		{
			return false;
		}

		FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true, ActorsToIgnore[0]);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

		// Ignore Actors
		TraceParams.AddIgnoredActors(ActorsToIgnore);

		// Reinitialize hit info
		HitOut = FHitResult(ForceInit);

		world->LineTraceSingleByChannel
		(
			HitOut,
			Start,
			End,
			CollisionChannel,
			TraceParams
		);

		return (HitOut.GetActor() != NULL);
	}

	static FORCEINLINE bool VTraceSphere(AActor* ActorToIgnore, const FVector& Start, const FVector& End,
		const float Radius, FHitResult& HitOut, ECollisionChannel TraceChannel = ECC_Pawn)
	{
		FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = false;

		// Ignore Actors
		TraceParams.AddIgnoredActor(ActorToIgnore);

		// Re-initialize hit info
		HitOut = FHitResult(ForceInit);

		// Get World Source
		TObjectIterator <APlayerController> ThePC;
		
		if (!ThePC) return false;

		return ThePC->GetWorld()->SweepSingleByChannel(
			HitOut,
			Start,
			End,
			FQuat(),
			TraceChannel,
			FCollisionShape::MakeSphere(Radius),
			TraceParams
		);
	}

public:
	UStaticFunctionLibrary();
};
