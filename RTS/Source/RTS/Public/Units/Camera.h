// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Camera.generated.h"

class AInfantryUnits;
class ASelectableUnits_AIController;
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Select();

	UPROPERTY(EditAnywhere, Category = "Spawn Properties")
	TSubclassOf <AActor> TargetClass;

	UPROPERTY(EditAnywhere, Category = "Spawn Properties")
	TSubclassOf <AInfantryUnits> ActorBP;

	UPROPERTY()
	TArray<AActor*> SpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Properties")
		TArray<AInfantryUnits*> UnitsArray;

	UPROPERTY(EditAnywhere, Category = "Enemy Spawn Properties")
	float LoopTime;

	UFUNCTION()
	void SpawnEnemies();

	void AttackMove();

	void CrushMove();

	void ReverseMove();

	void Stop();

	void Patrolling();

	void ForceAttack();

	void GetBPArray();

	template <typename T>
	static FORCEINLINE int32 GetBPArrayRef(UClass* TheBP, const FName& Name)
	{
		if (!TheBP)
		{
			UE_LOG(LogTemp, Warning, TEXT("No BP."));
			return -1;
		}
		if (Name == NAME_None)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Name"));
			return -1;
		}

		UArrayProperty* ArrayProp = FindField<UArrayProperty>(TheBP, Name);
		FScriptArray* ScriptArray = ((FScriptArray*)ArrayProp);

		if (ArrayProp != NULL && ScriptArray)
		{
			FScriptArrayHelper_InContainer BPArrayHelper(ArrayProp, ScriptArray->GetData());

			return BPArrayHelper.Num();
		}

		return -1;
	}
};
