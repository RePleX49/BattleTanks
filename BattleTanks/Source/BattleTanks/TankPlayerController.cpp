  // Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h" //must be first include
#include "Engine/World.h"
#include "BattleTanks.h"
#include "DrawDebugHelpers.h"

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
		//tell controlled tank to aim at the hit point
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	// GetLookVectorHitLocation to out param OutHitLocation
	if (!GetLookVectorHitLocation(ScreenLocation, OutHitLocation))
	{
		return false;
	}
	
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector2D ScreenLocation, FVector& HitLocation) const
{
	FHitResult Hit;
	FVector CameraWorldLocation;
	FVector LookDirection;

	// "De-project" the screen position of the crosshair to a world direction
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);

	FVector EndTrace = CameraWorldLocation + (LookDirection * LineTraceRange);

	// Line-trace along the LookDirection, and see what we hit
	if (GetWorld()->LineTraceSingleByChannel(Hit, CameraWorldLocation, EndTrace, ECC_Visibility))
	{
		// DrawDebugLine(GetWorld(), CameraWorldLocation, EndTrace, FColor(100, 0 ,0), true, -1, 0, 2);
		HitLocation = Hit.Location;
		return true;
	}

	HitLocation = FVector(0);
	return false;
}


