// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "Grid.h"
#include "TerrainGridComponent.h"

UTerrainGridComponent::UTerrainGridComponent()
{
	materialInstance = CreateDefaultSubobject<UMaterialInstance>(TEXT("Material Instance"));
}

