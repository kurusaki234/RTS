// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "TargetPointSelection.h"
#include "AITargetPoint.h"
#include "SelectableUnits_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTargetPointSelection::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ASelectableUnits_AIController* AICon = Cast<ASelectableUnits_AIController>(OwnerComp.GetAIOwner());

	/*If the Controller is valid:
	1)Get the Blackboard Component and the Current Point of the bot
	2)Search for the next point, which will be different from the Current Point*/
	if (AICon)
	{

		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
		AAITargetPoint* CurrentPoint = Cast<AAITargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvailableTargetPoints = AICon->GetAvailableTargetPoints();

		//This variable will contain a random index in order to determine the next possible point
		//int32 RandomIndex;

		//Here, we store the possible next target point
		AAITargetPoint* NextTargetPoint = nullptr;

		//Find a next point which is different from the current one
		if (AICon->CurrentPatrolPoint != AvailableTargetPoints.Num() - 1)
		{
			NextTargetPoint = Cast<AAITargetPoint>(AvailableTargetPoints[++AICon->CurrentPatrolPoint]);
		}
		else
		{
			NextTargetPoint = Cast<AAITargetPoint>(AvailableTargetPoints[0]);
			AICon->CurrentPatrolPoint = 0;
		}

		//Update the next location in the Blackboard so the bot can move to the next Blackboard value
		BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);

		//At this point, the task has been successfully completed*/
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}