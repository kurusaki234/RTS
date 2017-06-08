// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Rifleman_AIController.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ARifleman_AIController : public AAIController
{
	GENERATED_BODY()
	
	/*** Behavior tree component ref **/
	UBehaviorTreeComponent* BehaviorComp;

	/**********Black Board*********/

	// Blackboard component ref
	UBlackboardComponent* BlackboardComp;

	// Blackboard keys
	UPROPERTY(EditDefaultsOnly, Category = "AI Property")
	FName LocationToGoKey;

	/*******************************/

	// Store all the available targetPoint instances.
	TArray <AActor*> TargetPoints;

	// Possess is executed when the character we want to control is spawned.
	// Inside this function, we initialize the blackboard and start the behavior tree
	virtual void Possess(APawn* Pawn) override;

public:
	// Constructor
	ARifleman_AIController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

	FORCEINLINE TArray <AActor*> GetAvailableTargetPoints() { return TargetPoints; }
	
	int32 CurrentPatrolPoint = 0;
};
