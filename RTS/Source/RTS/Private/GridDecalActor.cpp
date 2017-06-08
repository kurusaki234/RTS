// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "GridDecalActor.h"

AGridDecalActor::AGridDecalActor()
{
	Decal = CreateDefaultSubobject <UDecalComponent>(TEXT("Decal Component"));
	Decal->RelativeScale3D = FVector(1.0, 1.0, 1.0);
	Decal->RelativeRotation = FRotator(-90.0f, 0.0f, 0.0f);

	RootComponent = Decal;

	SetActorRotation(FRotator(-90.0f, 0.0f, 0.0f));
}


