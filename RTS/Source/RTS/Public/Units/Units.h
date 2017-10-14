// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Units.generated.h"

class AFogOfWar;

UCLASS()
class RTS_API AUnits : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUnits();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		bool bIsAlly;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		bool bFogOfWar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		float fogOfWarRadius;

	AFogOfWar* m_fow = nullptr;
};
