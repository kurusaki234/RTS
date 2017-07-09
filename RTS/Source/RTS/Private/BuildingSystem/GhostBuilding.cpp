// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "Grid.h"
#include "StaticFunctionLibrary.h"
#include "GhostBuilding.h"

// Sets default values
AGhostBuilding::AGhostBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	grid = CreateDefaultSubobject <AGrid>(FName("GridComponent"));
	gridWidth = 0;
	gridDepth = 0;
	gridSize = 0;
	StartLocation = 0;
	Start = FVector(0);
	End = FVector(0);

	static ConstructorHelpers::FObjectFinder <UMaterialInstance> defaultObject
	(TEXT("MaterialInstance'/Game/Material/Mat_GridDefault_Inst.Mat_GridDefault_Inst'"));
	static ConstructorHelpers::FObjectFinder <UMaterialInstance> buildableObject
	(TEXT("MaterialInstance'/Game/Material/Mat_GridDefault_Inst.Mat_GridDefault_Inst'"));
	static ConstructorHelpers::FObjectFinder <UMaterialInstance> notBuildableObject
	(TEXT("MaterialInstance'/Game/Material/Mat_GridDecal_Inst.Mat_GridDecal_Inst'"));

	// Initialize grid material
	if (defaultObject.Object == nullptr)
	{
		return;
	}
	else
	{
		defaultMaterial = defaultObject.Object;

	}
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

// Called when the game starts or when spawned
void AGhostBuilding::BeginPlay()
{
	Super::BeginPlay();

	SpawnDecal();
	//UpdateDecal();
}

// Called every frame
void AGhostBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("Stored Location: %s, Current Component Location: %s"), *StoredLocation.ToString(),
		*GetRootComponent()->GetComponentLocation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Update Raycast Status: %s"), (GetUpdateRaycast()) ? TEXT("True") : TEXT("False"));

	//UpdateDecal();
	/*if (!GetUpdateRaycast())
	{
		
		StoredLocation = GetRootComponent()->GetComponentLocation();
		SetUpdateRaycast();
	}
	else
	{
		SetUpdateRaycast();
	}*/
}

void AGhostBuilding::SpawnDecal()
{
	buildableMaterial = buildableMaterial;
	notBuildableMaterial = notBuildableMaterial;

	if (GetSpawnDecal() == false)
	{
		StartLocation = GetActorLocation().X - gridSize * 3;

		int32 i = 0;

		grid->AddUninitialized(gridWidth, gridDepth);

		for (int y = 0; y < gridWidth; y++)
		{
			for (int x = 0; x < gridDepth; x++)
			{
				grid->gridTransform.X = StartLocation + (int32)i / gridDepth *  gridSize;
				grid->gridTransform.Y = StartLocation + (int32)i % gridWidth *  gridSize;
				grid->gridTransform.Z = 100;

				FGridProperty tempGrid
				(
					FVector(300.0f, gridSize / 2, gridSize / 2),
					FVector(grid->gridTransform),
					FRotator(-90.0f, 0.0f, 0.0f),	// -90.0 pitch rotation to get the correct decal rotation
					0.0
				);

				grid->gridMap.Rows[y].Columns[x] = tempGrid;
				grid->gridMap.Rows[y].Columns[x].SpawnDecal(GetRootComponent(), defaultMaterial, buildableMaterial,
					notBuildableMaterial);

				i++;
			}
		}
		SetSpawnDecal(true);
		//bInitialized = true;
	}
}

void AGhostBuilding::UpdateDecal()
{
	//UE_LOG(LogTemp, Warning, TEXT("%s"), GetRootComponent()->GetName());

	int32 i = 0;

	for (int y = 0; y < gridWidth; y++)
	{
		for (int x = 0; x < gridDepth; x++)
		{
			FHitResult HitInfo(ForceInit);

			//UBoxComponent* BoxComponent = CreateDefaultSubobject <UBoxComponent>(TEXT("Box Collision"));

			StoredLocation = GetRootComponent()->GetComponentLocation();

			Start = FVector(
				GetRootComponent()->GetComponentLocation().X - (gridSize * 3)
				+ ((int32)i / gridDepth *  gridSize),
				GetRootComponent()->GetComponentLocation().Y - (gridSize * 3)
				+ ((int32)i % gridWidth *  gridSize),
				0.0f);

			End = Start + GetActorUpVector() * Distance;

			/*if (GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, ECollisionChannel::ECC_WorldStatic))
			{
				if (HitInfo.GetActor()->ActorHasTag("Building"))
				{
					UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitInfo.GetActor()->GetName());
					//grid->gridMap.Rows[y].Columns[x].gridState = EGridState::GS_NotBuildable;
				}
			}
			else
			{
				/*UE_LOG(LogTemp, Warning, TEXT("Start Location: %s, End Location: %s, Start Value: %d"), *Start.ToString()
				, *End.ToString(), StartLocation);
				grid->gridMap.Rows[y].Columns[x].gridState = EGridState::GS_Buildable;
			}*/

			if (grid->gridMap.Rows[y].Columns[x].gridState == EGridState::GS_Buildable)
			{
				grid->gridMap.Rows[y].Columns[x].defaultDecalInstance->UnregisterComponent();
				grid->gridMap.Rows[y].Columns[x].buildableDecalInstance->RegisterComponent();
				grid->gridMap.Rows[y].Columns[x].notBuildableDecalInstance->UnregisterComponent();

			}
			else if (grid->gridMap.Rows[y].Columns[x].gridState == EGridState::GS_NotBuildable)
			{
				grid->gridMap.Rows[y].Columns[x].defaultDecalInstance->UnregisterComponent();
				grid->gridMap.Rows[y].Columns[x].buildableDecalInstance->UnregisterComponent();
				grid->gridMap.Rows[y].Columns[x].notBuildableDecalInstance->RegisterComponent();
			}
			else
			{
				grid->gridMap.Rows[y].Columns[x].defaultDecalInstance->RegisterComponent();
				grid->gridMap.Rows[y].Columns[x].buildableDecalInstance->UnregisterComponent();
				grid->gridMap.Rows[y].Columns[x].notBuildableDecalInstance->UnregisterComponent();
			}

			i++;
		}
	}
}

void AGhostBuilding::DestroyDecal()
{
	SetSpawnDecal(false);

	for (int y = 0; y < gridWidth; y++)
	{
		for (int x = 0; x < gridDepth; x++)
		{
			grid->gridMap.Rows[y].Columns[x].defaultDecalInstance->UnregisterComponent();
			grid->gridMap.Rows[y].Columns[x].buildableDecalInstance->UnregisterComponent();
			grid->gridMap.Rows[y].Columns[x].notBuildableDecalInstance->UnregisterComponent();
		}
	}
}

void AGhostBuilding::SetSpawnDecal(bool state)
{
	bSpawnDecal = state;
}

void AGhostBuilding::SetUpdateRaycast()
{
	bUpdateRaycast = (GetRootComponent()->GetComponentLocation() != StoredLocation) ? true : false;
}

