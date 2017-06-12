// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "Kismet/KismetMathLibrary.h"
#include "TerrainGrid.h"
#include "Grid.h"

// 2D World Dimension Array
//ATerrainGrid* gridArray[gridProperty.];

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	gridTransform = FVector(0);

	//Clear();
	static ConstructorHelpers::FObjectFinder <UMaterialInstance> buildableObject
	(TEXT("MaterialInstance'/Game/Material/Mat_DecalGrid_Inst.Mat_DecalGrid_Inst'"));
	static ConstructorHelpers::FObjectFinder <UMaterialInstance> notBuildableObject
	(TEXT("MaterialInstance'/Game/Material/Mat_GridDecal_Inst.Mat_GridDecal_Inst'"));

	// Initialize buildable material
	if (buildableObject.Object == nullptr)
	{
		return;
	}
	else
	{
		buildableMaterial = buildableObject.Object;
	}

	if (notBuildableObject.Object == nullptr)
	{
		return;
	}
	else
	{
		notBuildableMaterial = notBuildableObject.Object;
	}
}

AGrid::~AGrid()
{

}

// Called when the code compiled
void AGrid::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	buildableMaterial = buildableMaterial;
	notBuildableMaterial = notBuildableMaterial;

	// Spawn grid 
	if (!bSpawned)
	{
		AddUninitialized(maxWidth, maxDepth);

		int32 i = 0;
		
		for (int32 y = 0; y < maxWidth; y++)
		{
			for (int32 x = 0; x < maxDepth; x++)
			{
				gridTransform.X = defaultPosition + (int32)i / maxDepth * gridSize;
				gridTransform.Y = defaultPosition + (int32)i % maxWidth * gridSize;
				gridTransform.Z = 100;

				FGridProperty gridProperty(
					FVector(300.0f, gridSize, gridSize),
					FVector(gridTransform),
					FRotator(-90.0f, 0.0f, 0.0f),	// -90.0 pitch rotation to get the correct decal rotation
					5.0f
				);
			
				if (gridMap.Rows[y].Columns[x].gridState == EGridState::GS_Buildable)
				{
					gridProperty.materialInstance = buildableMaterial;
				}
				else if (gridMap.Rows[y].Columns[x].gridState == EGridState::GS_NotBuildable)
				{
					gridProperty.materialInstance = notBuildableMaterial;
				}
				
				//UE_LOG(LogTemp, Warning, TEXT("Material Instance: %s"), *gridProperty.materialInstance->GetName());

				gridMap.Rows[y].Columns[x] = gridProperty;
				gridMap.Rows[y].Columns[x].SpawnDecal(this);
				i++;
			}
		}
		
		bSpawned = true;
	}
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AGrid::AddUninitialized(const int32 RowCount, const int32 ColCount)
{
	// Add Rows
	for (int32 y = 0; y < RowCount; y++)
	{
		gridMap.AddNewRow();

		for (int32 x = 0; x < ColCount; x++)
		{
			gridMap.Rows[y].AddNewColumn();
		}
	}
}

void AGrid::Clear()
{
	if (gridMap.Rows.Num() <= 0) return;

	const int32	TotalRows = gridMap.Rows.Num();
	const int32 TotalCols = gridMap.Rows[0].Columns.Num();

	for (int32 y = 0; y < TotalRows; y++)
	{
		for (int32 x = 0; x < TotalCols; x++)
		{
			gridMap.Rows[y].Columns[x].Clear();
		}
	}

	// Empty 
	for (int32 y = 0; y < TotalRows; y++)
	{
		gridMap.Rows[y].Columns.Empty();
	}
	gridMap.Rows.Empty();
}



