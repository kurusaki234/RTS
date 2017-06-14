// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class RTS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	ATank* GetPlayerTank() const;

	ATank* GetControlledTank() const;
};
