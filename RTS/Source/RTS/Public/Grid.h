// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Grid.generated.h"

UENUM()
enum class EGridState : uint8
{
	GS_Buildable		UMETA(DisplayName = "Buildable"),
	GS_NotBuildable		UMETA(DisplayName = "Not Buildable")
};

USTRUCT()
struct FGridProperty
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FVector Scale;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FRotator Rotation;

	UPROPERTY()
	float LifeSpan;

	UPROPERTY()
	UMaterialInstance* materialInstance = nullptr;

	UPROPERTY()
	UDecalComponent* defaultDecalInstance = nullptr;

	UPROPERTY()
	UDecalComponent* buildableDecalInstance = nullptr;

	UPROPERTY()
	UDecalComponent* notBuildableDecalInstance = nullptr;

	EGridState gridState = EGridState::GS_Buildable;

	void Clear()
	{
		if (bIsValid())
		{
			defaultDecalInstance->UnregisterComponent();
			defaultDecalInstance = NULL;
		}
	}

	bool bIsValid() const
	{
		return (gridState == EGridState::GS_Buildable);
	}

	void SpawnDecal(USceneComponent* object, UMaterialInstance* defaultInstance, UMaterialInstance* buildableInstance
		,UMaterialInstance* notBuildableInstance)
	{
		defaultDecalInstance = UGameplayStatics::SpawnDecalAttached
						(
							defaultInstance,
							Scale,
							object,
							NAME_None,
							Location,
							Rotation,
							EAttachLocation::KeepWorldPosition,
							LifeSpan
						);

		buildableDecalInstance = UGameplayStatics::SpawnDecalAttached
		(
			buildableInstance,
			Scale,
			object,
			NAME_None,
			Location,
			Rotation,
			EAttachLocation::KeepWorldPosition,
			LifeSpan
		);

		notBuildableDecalInstance = UGameplayStatics::SpawnDecalAttached
		(
			notBuildableInstance,
			Scale,
			object,
			NAME_None,
			Location,
			Rotation,
			EAttachLocation::KeepWorldPosition,
			LifeSpan
		);
	}
	
	FGridProperty() {}

	FGridProperty(const FVector& _Scale, const FVector& _Location, const FRotator& _Rotation, float _LifeSpan)
		: Scale(_Scale), Location(_Location), Rotation(_Rotation), LifeSpan(_LifeSpan)
	{}
};

USTRUCT()
struct FGridCol
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray <FGridProperty> Columns;

	void AddNewColumn()
	{
		Columns.Add(FGridProperty());
	}

	FGridCol()
	{

	}
};

USTRUCT()
struct FGridRow
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray <FGridCol> Rows;

	void AddNewRow()
	{
		Rows.Add(FGridCol());
	}

	FGridRow()
	{}
};

UCLASS()
class RTS_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();
	~AGrid();

public:	
	UPROPERTY()
	FVector gridTransform;

	UPROPERTY(EditAnywhere, Category = "Setup")
	bool bSpawned = false;

	UPROPERTY(EditAnywhere, Category = "Setup")
	int32 defaultPosition;

	UPROPERTY(EditAnywhere, Category = "Setup")
	FGridRow gridMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int32 maxWidth;		// Grid Width	(x)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int32 maxDepth;		// Grid Depth	(y)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int32 gridSize;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* buildableMaterial = nullptr;
	
	UPROPERTY(EditAnywhere)
	UMaterialInstance* notBuildableMaterial = nullptr;

	void AddUninitialized(const int32 RowCount, const int32 ColCount);

	void Clear();
};
