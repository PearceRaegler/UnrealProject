// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealProjectGameInstance.h"
#include "Kismet/GameplayStatics.h"


void UUnrealProjectGameInstance::LeaveGame()
{
	auto world = GEngine->GetCurrentPlayWorld();
	UGameplayStatics::OpenLevel(world, FName(TEXT("/Game/FirstPerson/Maps/MenuMap.MenuMap")));
}

void UUnrealProjectGameInstance::StartGame()
{
	auto world = GEngine->GetCurrentPlayWorld();
	UGameplayStatics::OpenLevel(world, FName(TEXT("/Game/FirstPerson/Maps/GameMap.GameMap")));
}