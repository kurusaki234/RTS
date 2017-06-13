// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "Rifleman.h"
#include "Rifleman_AIController.h"
#include "SpawnPoint.h"
#include "Camera.h"


// Sets default values
ACamera::ACamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/** Setup Camera Movement Component **/
	/*CameraBoom = CreateDefaultSubobject <UCameraComponent>(TEXT("Camera"));
	CameraBoom->AttachTo(RootComponent);

	Origin = CreateDefaultSubobject <UArrowComponent>(TEXT("Origin"));
	Origin->AttachTo(RootComponent);*/
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
		FVector NewLocation = FVector(FoundActors[i]->GetRootComponent()->GetSocketLocation("SpawnLocation").X,
			FoundActors[i]->GetRootComponent()->GetSocketLocation("SpawnLocation").Y, 
			FoundActors[i]->GetRootComponent()->GetSocketLocation("SpawnLocation").Z);

		ARifleman* rifleman = World->SpawnActor<ARifleman>(ActorBP, NewLocation,
			FRotator::ZeroRotator, SpawnInfo);

		rifleman->SetActorScale3D(FVector(0.4));
		rifleman->GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	}
}

void ACamera::SpawnEnemies()
{
	FActorSpawnParameters SpawnInfo;

	TArray<AActor*> SpawnPoints;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TargetBotClass, SpawnPoints);

	UE_LOG(LogTemp, Warning, TEXT("%d"), RandomValue);

	//FVector NewLocation = SpawnPoints[RandomValue]->GetTargetLocation();

	if (SpawnPoints[RandomValue] != nullptr)
	{
		ARifleman* rifleman = GetWorld()->SpawnActor<ARifleman>(ActorBP, SpawnPoints[RandomValue]->GetTargetLocation(), FRotator::ZeroRotator, SpawnInfo);

		rifleman->SetActorScale3D(FVector(0.4));

		rifleman->GetCharacterMovement()->MaxWalkSpeed = 200.0f;

		rifleman->AIControllerType = ControllerType::CT_Bot; 
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GG"));
	}
	
	RandomValue = FMath::RandRange(0, SpawnPoints.Num() - 1);
}
