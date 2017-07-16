// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "RTS_UI.h"
#include "StaticFunctionLibrary.h"
#include "RTSPlayerController.h"
#include "FogOfWar.h"

ARTSPlayerController::ARTSPlayerController()
{
	
}

void ARTSPlayerController::Possess(APawn* OwnerPawn)
{
	Super::Possess(OwnerPawn);

	/*if (RTSUIWidgetBP)
	{
		RTSUIWidget = CreateWidget <URTS_UI>(this, RTSUIWidgetBP);

		RTSUIWidget->AddToViewport();
	}*/
}

void ARTSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	m_fow->SpawnActor(AFogOfWar::StaticClass());

	m_fow->revealSmoothCircle(FVector2D(100, 100), 30);
}

void ARTSPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*FVector LookDirection;
	FVector2D MousePos;

	GetMousePosition(MousePos.X, MousePos.Y);

	if (GetMouseWorldPosition(MousePos, LookDirection))
	{
		FHitResult HitResult;
		//auto StartLocation = MousePos;
	}*/
	//GetHitResultUnderCursorByChannel()
}

/*bool ARTSPlayerController::GetMouseWorldPosition(FVector2D MousePos, FVector& LookDirection) const
{
	UWorld* world = GetWorld();

	FVector WorldPos;

	if (world != nullptr)
	{
		WorldPos = FVector(MousePos.X, MousePos.Y, 0);
		LookDirection = FVector(0, 0, 0);
	}

	return (DeprojectMousePositionToWorld(WorldPos, LookDirection));
}*/


