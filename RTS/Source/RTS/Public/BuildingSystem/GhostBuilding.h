// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Grid.h"
#include "GhostBuilding.generated.h"

UCLASS()
class RTS_API AGhostBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGhostBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
	int32 gridWidth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
	int32 gridDepth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
	int32 gridSize;

	UPROPERTY()
	FVector GridLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
	UMaterialInstance* defaultMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
	UMaterialInstance* buildableMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid")
	UMaterialInstance* notBuildableMaterial = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Decal")
	void SpawnDecal();

	UFUNCTION(BlueprintCallable, Category = "Decal")
	void UpdateDecal();

	UFUNCTION(BlueprintCallable, Category = "Decal")
	void DestroyDecal();

	/*** Basic Getters and Setters ***/
	UFUNCTION()
	void SetSpawnDecal(bool state);

	UFUNCTION()
	FORCEINLINE bool GetSpawnDecal() const { return bSpawnDecal; }

	UPROPERTY(EditAnywhere, Category = "Raycast")
	float Distance;

	/*** Tick the raycast only when the ghost mesh moved ***/
	UPROPERTY()
	FVector StoredLocation;

	UFUNCTION()
	FORCEINLINE bool GetUpdateRaycast() const { return bUpdateRaycast; }

	UFUNCTION()
	void SetUpdateRaycast();

private:
	AGrid* grid = nullptr;

	UPROPERTY()
	bool bSpawnDecal = false;

	UPROPERTY()
	bool bUpdateRaycast = false;

	/*** Raycast Properties ***/
	UPROPERTY()
	FVector Start;

	UPROPERTY()
	FVector End;
	/*****************************/

	UPROPERTY()
	int32 StartLocation;

	TArray<FGridProperty> tempGridArray;

	UPROPERTY()
	USceneComponent* sceneComponent;
};
