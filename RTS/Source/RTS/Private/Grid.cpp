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
	PrimaryActorTick.bCanEverTick = false;
}

AGrid::~AGrid()
{

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



