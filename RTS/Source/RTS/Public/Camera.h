// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Camera.generated.h"

class ARifleman;
class ARifleman_AIController;

UCLASS()
class RTS_API ACamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Select();

	void QuickSpawn();

	UPROPERTY(EditAnywhere, Category = "Spawn Properties")
	TSubclassOf <AActor> TargetClass;

	UPROPERTY(EditAnywhere, Category = "Spawn Properties")
	TSubclassOf <ARifleman> ActorBP;
};
