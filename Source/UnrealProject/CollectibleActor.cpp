// Fill out your copyright notice in the Description page of Project Settings.

#include "CollectibleActor.h"
#include "UnrealProjectCharacter.h"
#include "SpawnPointActor.h"
#include "Kismet/GameplayStatics.h"
#include "ScoreWidget.h"
#include "UnrealProjectCharacter.h"

// Sets default values
ACollectibleActor::ACollectibleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(_StaticMesh);
}

// Called when the game starts or when spawned
void ACollectibleActor::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ACollectibleActor::OnCollectibleBeginOverlap);

	// get a collection of all spawnpoints on the map
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPointActor::StaticClass(), PointsArr);

	MoveToNewLocation();
}

void ACollectibleActor::OnCollectibleBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) {
	//UE_LOG(LogTemp, Log, TEXT("Collision Detected"));

	// find if other actor is the player
	auto player = Cast<AUnrealProjectCharacter>(OtherActor);
	
	// move outside of the map, then to another location some time later
	if (player) {
		TeleportTo(FVector(0.0f,0.0f,-100.0f), FRotator(0.0f, 0.0f, 0.0f));

		// add to the player's score
		player->OnScoreChanged(Score);

		// run the move to new location after a random amount of time
		FTimerHandle TimerHandle;

		GetWorldTimerManager().SetTimer(TimerHandle, this, &ACollectibleActor::MoveToNewLocation, FMath::RandRange(10.0f, 20.0f), false); // Executes MyFunction after 2 seconds
	}
}

void ACollectibleActor::MoveToNewLocation() {
	// move the collecible to a random spawnpoint's location
	if (PointsArr.Num() > 0) {
		int32 rand = FMath::RandRange(0, PointsArr.Num() - 1);

		TeleportTo(PointsArr[rand]->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("SpawnPoint not found"));
	}
}
