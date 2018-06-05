  // Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h" //must be first include
#include "Engine/World.h"
#include "BattleTanks.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();

	// Check that we are in fact possessing a tank
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
	// Check if we're possessing a tank
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation)) // side effect is going to line trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		//tell controlled tank to aim at the hit point
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	FVector LookDirection;

	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("Location Direction: %s"), *LookDirection.ToString());
	}
	
	// Line-trace along the LookDirection, and see what we hit
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
	);
}