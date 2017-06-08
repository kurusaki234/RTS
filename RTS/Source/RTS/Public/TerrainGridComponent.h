// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/InstancedStaticMeshComponent.h"
#include "TerrainGridComponent.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API UTerrainGridComponent : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Components|InstancedStaticMesh")
	virtual int32 AddInstance(const FTransform& InstanceTransform);
};
