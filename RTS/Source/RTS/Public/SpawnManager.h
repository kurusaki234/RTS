// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "SpawnManager.generated.h"

/**
 * 
 */
UENUM()
enum class EBuildingType : uint8
{
	BT_Barrack		UMETA(DisplayName = "Barrack"),
};

UCLASS()
class RTS_API USpawnManager : public UObject
{
	GENERATED_BODY()

	//APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

	/*if (PlayerController != nullptr)
	{
		// if player select the unit name BT_Barrack, then able to spawn infantry unit at the HUD selection


	}*/
	
	
};
