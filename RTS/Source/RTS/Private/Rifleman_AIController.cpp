// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "Rifleman.h"
#include "AITargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Rifleman_AIController.h"

ARifleman_AIController::ARifleman_AIController()
{
	// Initialize blackboard and behavior tree
	BehaviorComp = CreateDefaultSubobject <UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject <UBlackboardComponent>(TEXT("BlackboardComp"));

	// Initialize blackboard keys
	LocationToGoKey = "LocationToGo";
}

void ARifleman_AIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	// Get reference to the character
	ARifleman* AICharacter = Cast <ARifleman>(Pawn);

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


