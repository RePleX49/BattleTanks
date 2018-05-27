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

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}
	else
	{
		//get world location if line trace through crosshair
		//if hit landscape
			//tell controlled tank to aim at the hit point
	}
}


