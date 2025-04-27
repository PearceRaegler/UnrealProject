// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "EnemyMonsterCharacter.h"

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
			MoveToActor(DetectedPawn, 90.0f);

		}
		// otherwise, return to wander
		else {

		}
	}
}