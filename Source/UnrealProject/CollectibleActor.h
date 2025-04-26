// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectibleActor.generated.h"

UCLASS()
class UNREALPROJECT_API ACollectibleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectibleActor();

	UPROPERTY(EditAnywhere, Category = "Score")
	int32 Score = 10;

	UPROPERTY(EditAnywhere, Category = "SpawnPoints")
	TArray<AActor*> PointsArr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* _StaticMesh;

	UFUNCTION()
	void OnCollectibleBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	void MoveToNewLocation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
