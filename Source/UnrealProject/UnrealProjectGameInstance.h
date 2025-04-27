// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UnrealProjectGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJECT_API UUnrealProjectGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Map Switching")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "Map Switching")
	void LeaveGame();
};
