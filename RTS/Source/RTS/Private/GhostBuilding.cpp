// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "GhostBuilding.h"


// Sets default values
AGhostBuilding::AGhostBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGhostBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGhostBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

