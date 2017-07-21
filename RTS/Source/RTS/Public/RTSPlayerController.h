// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"

/**
 * 
 */

class URTS_UI;
class AFogOfWar;

UCLASS()
class RTS_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()

	ARTSPlayerController();

	virtual void Possess(APawn* OwnerPawn) override;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	AFogOfWar* m_fow = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	bool bHiddenFogOfWar;

	/*bool GetMouseWorldPosition(FVector2D MousePos, FVector& LookDirection) const;

protected:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf <URTS_UI> RTSUIWidgetBP;

private:
	// UI Reference
	URTS_UI* RTSUIWidget;*/
};
