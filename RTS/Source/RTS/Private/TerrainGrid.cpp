// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "TerrainGrid.h"

ATerrainGrid::ATerrainGrid()
{
	// Static Mesh
	static ConstructorHelpers::FObjectFinder <UStaticMesh> StaticMeshObject
	(TEXT("StaticMesh '/Engine/EngineMeshes/Cube.Cube'"));

	SM_GridPlane = StaticMeshObject.Object;

	// Create New Object
	InstancedStaticMeshComponent = CreateDefaultSubobject <UInstancedStaticMeshComponent>
		 (TEXT("InstancedStaticMeshComponent"));
	InstancedStaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform,
		FName("InstancedMesh"));

	if (!InstancedStaticMeshComponent) return;

	// Setup Instanced Static Mesh Component
	InstancedStaticMeshComponent->SetStaticMesh(SM_GridPlane);
	InstancedStaticMeshComponent->bOwnerNoSee = false;

	InstancedStaticMeshComponent->bCastDynamicShadow = false;
	InstancedStaticMeshComponent->CastShadow = false;

	// Visibility
	InstancedStaticMeshComponent->SetHiddenInGame(false);

	// Mobility
	InstancedStaticMeshComponent->SetMobility(EComponentMobility::Movable);

	// Collision
	InstancedStaticMeshComponent->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InstancedStaticMeshComponent->BodyInstance.SetObjectType(ECC_WorldDynamic);
	InstancedStaticMeshComponent->BodyInstance.SetResponseToAllChannels(ECR_Ignore);
	InstancedStaticMeshComponent->BodyInstance.SetResponseToChannel(ECC_WorldStatic, ECR_Block);

	if (!StaticMeshComponent) return;
	
	// Setup Grid Plane
	// Mobility
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);

	// Collision 
	StaticMeshComponent->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StaticMeshComponent->BodyInstance.SetObjectType(ECC_WorldDynamic);
	StaticMeshComponent->BodyInstance.SetResponseToChannel(ECC_WorldStatic, ECR_Block);
	StaticMeshComponent->BodyInstance.SetResponseToChannel(ECC_WorldDynamic, ECR_Block);
}


