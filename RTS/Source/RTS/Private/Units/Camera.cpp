// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "SelectableUnits.h"
#include "SelectableUnits_AIController.h"
#include "SpawnPoint.h"
#include "Camera.h"


// Sets default values
ACamera::ACamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACamera::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACamera::SpawnEnemies, LoopTime, true);
}

// Called every frame
void ACamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Select", IE_Pressed, this, &ACamera::Select);
}

void ACamera::Select()
{

}

void ACamera::SpawnEnemies()
{
	FActorSpawnParameters SpawnInfo;

	UWorld* const World = GetWorld();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoint::StaticClass() , SpawnPoints);

	if (SpawnPoints.Num() > 0)
	{
		int32 randomSpawnValue = FMath::RandRange(0, SpawnPoints.Num() - 1);

		FVector NewLocation = SpawnPoints[randomSpawnValue]->GetActorLocation();

		ASelectableUnits* SelectableUnits = World->SpawnActor<ASelectableUnits>(ActorBP, NewLocation, FRotator::ZeroRotator, SpawnInfo);

		SelectableUnits->SetActorScale3D(FVector(0.4));

		SelectableUnits->GetCharacterMovement()->MaxWalkSpeed = 200.0f;

		SelectableUnits->AIControllerType = ControllerType::CT_Bot;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Please put spawn points in order to spawn enemies"));
	}
}
