// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "Rifleman.h"
#include "Rifleman_AIController.h"
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
	PlayerInputComponent->BindAction("Spawn", IE_Pressed, this, &ACamera::QuickSpawn);
}

void ACamera::Select()
{

}

void ACamera::QuickSpawn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("HELLO"));
	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TargetClass, FoundActors);

	FActorSpawnParameters SpawnInfo;

	UWorld* const World = GetWorld();

	for (int i = 0; i < FoundActors.Num(); i++)
	{
		FVector NewLocation = FVector(FoundActors[i]->GetActorLocation().X - 500.0f, 
			FoundActors[i]->GetActorLocation().Y - 500.0f,
			205.0f);

		ARifleman* rifleman = World->SpawnActor<ARifleman>(ActorBP, NewLocation,
			FRotator::ZeroRotator, SpawnInfo);
	}
}


