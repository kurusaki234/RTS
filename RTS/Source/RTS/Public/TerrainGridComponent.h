// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/InstancedStaticMeshComponent.h"
#include "TerrainGridComponent.generated.h"

/**
 * 
 */
// Forward declarations
//AGrid* gridClass;

UCLASS()
class RTS_API UTerrainGridComponent : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Consturctor
	UTerrainGridComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int32 buildingWidth;	// (x)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int32 buildingDepth;	// (y)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int32 gridSize;

	UPROPERTY(EditAnywhere, Category = "Setup")
	UMaterialInstance* materialInstance = nullptr;
};
