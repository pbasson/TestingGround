//AUTHOR:PREETPAL_BASSON
//PURPOSE :

#include "ChooseWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"



EBTNodeResult::Type UChooseWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{


	//Get Patrol Points
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	auto PatrolPoint = PatrolRoute->GetPatrolPoints();
	//Set Next Waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoint[Index]);

	//Cycle through Waypoints
	auto NextIndex = (Index + 1) % PatrolPoint.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}
