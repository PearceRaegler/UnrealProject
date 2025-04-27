// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "EnemyMonsterCharacter.generated.h"

UCLASS()
class UNREALPROJECT_API AEnemyMonsterCharacter : public ACharacter
{
	GENERATED_BODY()

// public properties
public:
	// Sets default values for this character's properties
	AEnemyMonsterCharacter();

// protected functions
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

// public functions
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy")
	void Chase(APawn* targetPawn);

// protected properties
protected:
	APawn* _chasedTarget = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAISenseConfig_Sight* sightConfig;

};
