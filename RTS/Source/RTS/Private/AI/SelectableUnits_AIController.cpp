// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "InfantryUnits.h"
#include "AITargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "SelectableUnits_AIController.h"

ASelectableUnits_AIController::ASelectableUnits_AIController()
{
	// Initialize blackboard and behavior tree
	BehaviorComp = CreateDefaultSubobject <UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject <UBlackboardComponent>(TEXT("BlackboardComp"));

	// Initialize blackboard keys
	LocationToGoKey = "LocationToGo";
}

void ASelectableUnits_AIController::Possess(APawn* OwnerPawn)
{
	Super::Possess(OwnerPawn);

	// Get reference to the character
	AInfantryUnits* AICharacter = Cast <AInfantryUnits>(OwnerPawn);

	if (AICharacter)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}

		// Populate patrol point array
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAITargetPoint::StaticClass(), TargetPoints);

		BehaviorComp->StartTree(*AICharacter->BehaviorTree);
	}
}


