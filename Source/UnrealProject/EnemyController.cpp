// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "EnemyMonsterCharacter.h"
#include "NavigationSystem.h"

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
			if (LineOfSightTo(DetectedPawn)) {
				//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Chasing"));
				EnemyPawn->SetChaseSpeed();
				MoveToActor(DetectedPawn, 10.0f);
			}
			else {
				// wander
				//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, TEXT("Line of Sight Lost"));
				ClearFocus(EAIFocusPriority::Gameplay);
				StopMovement();
				EnemyPawn->SetWanderSpeed();
				//GoToRandomPoint(1200.0f);
			}
		}
		// otherwise, return to wander
		else {
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, TEXT("Line of Sight Lost"));
			EnemyPawn->SetWanderSpeed();
			ClearFocus(EAIFocusPriority::Gameplay);
			StopMovement();
			// set random nav point to go to
			//GoToRandomPoint(1200.0f);
		}
	}
}
/*
void AEnemyController::GoToRandomPoint(float Radius)
{
	// Get the pawn's location
	FVector CurrentLocation = GetPawn()->GetActorLocation();

	// Get the navigation system
	UNavigationSystemV1* NavArea = UNavigationSystemV1::UNavigationSystemV1::GetNavigationSystem(GetWorld());

	// Check if the navigation system exists
	if (NavArea != nullptr)
	{
		// Find a random reachable point
		FNavLocation RandomTargetLocation = FNavLocation(CurrentLocation);

		// If a random reachable point was found
		if (NavArea->GetRandomReachablePointInRadius(CurrentLocation, Radius, RandomTargetLocation))
		{
			// Move the pawn to the random location
			MoveToLocation(RandomTargetLocation.Location, 5.0f);
		}
	}
}
*/
