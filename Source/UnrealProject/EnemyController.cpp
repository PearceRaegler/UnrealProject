// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "EnemyMonsterCharacter.h"
//#include "NavigationSystem.h"

void AEnemyController::BeginPlay() {
	Super::BeginPlay();
	APawn* ControlledPawn = GetPawn();

	if (ControlledPawn) {
		AIPerceptionComponent = ControlledPawn->FindComponentByClass<UAIPerceptionComponent>();
	}

	if (AIPerceptionComponent) {
		AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemyController::PerceptionUpdated);
	}
}

void AEnemyController::PerceptionUpdated(const TArray<AActor*>& UpdatedActors) {
	for (AActor* Actor : UpdatedActors)
	{
		if (!Actor) continue;
		APawn* DetectedPawn = Cast<APawn>(Actor);
		APawn* ControlledPawn = GetPawn();
		AEnemyMonsterCharacter* EnemyPawn = Cast<AEnemyMonsterCharacter>(ControlledPawn);
		// chase the player
		if (DetectedPawn) {
			EnemyPawn->SetChaseSpeed();
			MoveToActor(DetectedPawn, 10.0f);

		}
		// otherwise, return to wander
		else {
			EnemyPawn->SetWanderSpeed();
			// set random nav point to go to
			//MoveToRandomReachablePoint(300.0f);
		}
	}
}
/*
void AEnemyController::MoveToRandomReachablePoint(float Radius)
{
	// Get the pawn's location
	const FVector CurrentLocation = GetPawn()->GetActorLocation();

	// Get the navigation system
	UNavigationSystemV1* NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	// Check if the navigation system exists
	if (NavArea)
	{
		// Find a random reachable point
		FNavLocation RandomTargetLocation;
		bool bFound = NavArea->GetRandomReachablePointInRadius(CurrentLocation, Radius, RandomTargetLocation);

		// If a random reachable point was found
		if (bFound)
		{
			// Move the pawn to the random location
			MoveToLocation(RandomTargetLocation.Location, false, false, false); // Consider passing appropriate parameters as needed
		}
	}
}
*/