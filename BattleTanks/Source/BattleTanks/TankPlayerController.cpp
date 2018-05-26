// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h" //must be first include
#include "BattleTanks.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is not currently possessing a tank")); 
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessed %s"), *ControlledTank->GetName());
	}
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}




