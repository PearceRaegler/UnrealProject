// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMonsterCharacter.h"
#include "Perception/PawnSensingComponent.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyController.h"
#include "EnemyAnimInstance.h"

// Sets default values
AEnemyMonsterCharacter::AEnemyMonsterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Assign the custom controller class
	AIControllerClass = AEnemyController::StaticClass();

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	sightConfig->SightRadius = 2200.0f; //max distance for sight
	sightConfig->LoseSightRadius = 800.0f; //when it loses sight of seen target
	sightConfig->PeripheralVisionAngleDegrees = 125.0f;
	sightConfig->DetectionByAffiliation.bDetectEnemies = false;
	sightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	AIPerceptionComponent->ConfigureSense(*sightConfig);
	AIPerceptionComponent->SetDominantSense(sightConfig->GetSenseImplementation());

}

// Called when the game starts or when spawned
void AEnemyMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AEnemyMonsterCharacter::Chase(APawn* targetPawn)
{
	_chasedTarget = targetPawn;

	//auto animInst = GetMesh()->GetAnimInstance();
	//auto enemyAnimInst = Cast<UEnemyAnimInstance>(animInst);
	if (targetPawn != nullptr)
	{
		auto enemyController = Cast<AEnemyController>(GetController());
		//_isChasing = true;
		//enemyController->MoveToActor(targetPawn, 90.0f);
	}
}

void AEnemyMonsterCharacter::SetChaseSpeed() {
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
}

void AEnemyMonsterCharacter::SetWanderSpeed() {
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}

