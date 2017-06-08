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
}

AGrid::~AGrid()
{

}

// Called when the code compiled
void AGrid::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	// Spawn Parameters for static mesh instantiation
	/*// Spawn Info
	FActorSpawnParameters spawnInfo;

	spawnInfo.bNoFail = true;*/

	// Spawn grid 
	if (!bSpawned)
	{
		/*for(auto& decal : DecalArray)
		{
			decal->DestroyComponent();
		}*/
	
		/*AddUninitialized(maxWidth, maxDepth);

		for (int y = 0; y < maxWidth; y++)
		{
			for (int x = 0; x < maxDepth; x++)
			{
				gridTransform.X = defaultPosition + (int)x / maxDepth * tileSize;
				gridTransform.Y = defaultPosition + (int)x % maxWidth * tileSize;
				gridTransform.Z = 100;

				FGridProperty gridProperty(
					FVector(300.0f, tileSize, tileSize),
					FVector(gridTransform),
					FRotator(-90.0f, 0.0f, 0.0f),	// -90.0 pitch rotation to get the correct decal rotation
					500.0f
				);

				if (gridMap.Rows[y].Columns[x].gridState == EGridState::GS_Buildable)
				{
					gridProperty.materialInstance = ConstructorHelpers::FObjectFinder <UMaterialInstance>
						(TEXT("Material'/Game/Material/Mat_DecalGrid_Inst'")).Object;
				}
				else if (gridMap.Rows[y].Columns[x].gridState == EGridState::GS_NotBuildable)
				{
					gridProperty.materialInstance = ConstructorHelpers::FObjectFinder <UMaterialInstance>
						(TEXT("Material'/Game/Material/Mat_DecalGrid_Inst'")).Object;
				}
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("HELLO"));
				UE_LOG(LogTemp, Warning, TEXT("Material Instance: %s"), *gridProperty.materialInstance->GetName());

				gridMap.Rows[y].Columns[x] = gridProperty;
				gridMap.Rows[y].Columns[x].SpawnDecal(this);
			}
		}
		*/
		for (int i = 0; i < maxWidth * maxDepth; i++)
		{
			gridTransform.X = defaultPosition + (int)i / maxDepth * tileSize;
			gridTransform.Y = defaultPosition + (int)i % maxWidth * tileSize;
			gridTransform.Z = 100;



			/** Decal Instantiation **/
			UDecalComponent* tempDecal = UGameplayStatics::SpawnDecalAtLocation
			(
				this,
				materialInstance,
				FVector(300.0f, tileSize, tileSize),
				FVector(gridTransform),
				FRotator(-90.0f, 0.0f, 0.0f),	// -90.0 pitch rotation to get the correct decal rotation
				500.0f
			);

			// Store inside to an array so we can register or unregister it whenever we need
			//DecalArray.Add(tempDecal);

			// Store x, y and z value into a 3D array / vector for grid building system
			

			/** Static Mesh Instantiation **/
			/*FTransform newTransform = FTransform
			(
			FRotator::ZeroRotator,
			FVector(gridTransform),
			FVector(gridProperty.tileSize / 250.0f, gridProperty.tileSize / 250.0f, 0.01f)
			);

			ATerrainGrid* newGrid = GetWorld()->SpawnActor<ATerrainGrid>(
			ATerrainGrid::StaticClass(),
			newTransform,
			spawnInfo);

			if (!newGrid) return;
			if (!newGrid->InstancedStaticMeshComponent) return;

			newGrid->InstancedStaticMeshComponent->AddInstance(UKismetMathLibrary::Conv_VectorToTransform(FVector(0)));
			newGrid->InstancedStaticMeshComponent->SetMaterial(0, materialInstance);*/

			//UE_LOG(LogTemp, Warning, TEXT("Tile Counter: %d spawned at %s"), i, *newGrid->GetActorLocation().ToString());
		}
		bSpawned = true;
	}
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();

	//static ConstructorHelpers::FObjectFinder<UMaterial> Material (TEXT("Material'/Game/Material/Mat_GridDecal.Mat_GridDecal'"));

	//UMaterialInterface* decalMaterial = (UMaterial*)Decal.Object;

	
	/*if (Decal.Object != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found"));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find any decal file."));
	}*/
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



