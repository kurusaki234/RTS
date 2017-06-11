// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "TerrainGrid.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ATerrainGrid : public AStaticMeshActor
{
	GENERATED_BODY()

	ATerrainGrid();

public:
	UPROPERTY()
	UInstancedStaticMeshComponent* InstancedStaticMeshComponent;
	
	UPROPERTY()
	UStaticMesh* SM_GridPlane;
};
