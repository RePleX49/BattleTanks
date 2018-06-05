// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h" //must be first include
#include "Engine/World.h"
#include "BattleTanks.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();

	// Check for player tank in the world
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AI can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI found player: %s"), *PlayerTank->GetName());
	}
}

ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	// Check if there is player pawn
	if (!PlayerPawn)
	{
		return nullptr;
	}
	else
	{
		return Cast<ATank>(PlayerPawn);
	}
}