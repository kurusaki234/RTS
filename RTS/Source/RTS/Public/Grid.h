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

	UDecalComponent* decalInstance = nullptr;

	EGridState gridState = EGridState::GS_Buildable;

	void Clear()
	{
		decalInstance = NULL;

		if (bIsValid())
		{
			decalInstance->UnregisterComponent();
			decalInstance = NULL;
		}
	}

	bool bIsValid() const
	{
		return (gridState == EGridState::GS_Buildable);
	}

	void SpawnDecal(UObject* object)
	{
		decalInstance = UGameplayStatics::SpawnDecalAtLocation
						(
							object,
							materialInstance,
							Scale,
							Location,
							Rotation,
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

protected:
	virtual void OnConstruction(const FTransform& transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
	float tileSize;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* materialInstance;

private:
	void AddUninitialized(const int32 RowCount, const int32 ColCount);

	void Clear();
};
