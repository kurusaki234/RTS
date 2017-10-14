// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"

/**
 * 
 */

UCLASS()
class RTS_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARTSPlayerController();

	virtual void Possess(APawn* OwnerPawn) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	/*bool GetMouseWorldPosition(FVector2D MousePos, FVector& LookDirection) const;

protected:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf <URTS_UI> RTSUIWidgetBP;

private:
	// UI Reference
	URTS_UI* RTSUIWidget;*/
};
