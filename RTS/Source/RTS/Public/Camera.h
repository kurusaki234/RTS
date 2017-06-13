// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Camera.generated.h"

class ARifleman;
class ARifleman_AIController;
class ASpawnPoint;

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

	UPROPERTY()
	UCameraComponent* CameraBoom = nullptr;

	UPROPERTY()
	UArrowComponent* OriginPoint = nullptr;

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

	UPROPERTY(EditAnywhere, Category = "Spawn Properties")
	TSubclassOf <AActor> TargetBotClass;

	UPROPERTY(EditAnywhere, Category = "Enemy Spawn Properties")
	float LoopTime;

	UFUNCTION()
	void SpawnEnemies();

	UPROPERTY()
	int32 RandomValue = 0;

	/** Camera Movement Component **/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	bool bRotateCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraZAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraHeightAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float RotateSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ZoomSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float RadiusMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float RadiusMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float EdgeForwardAxis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float EdgeRightAxis;
};
