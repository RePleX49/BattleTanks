// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "public/Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be last include

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	ATank* GetControlledTank() const;
	
	// called only once when begin play
	virtual void BeginPlay() override;

	// called on every frame
	virtual void Tick(float DeltaTime) override;

	// aims barrel towards crosshair in 3D space
	void AimTowardsCrosshair();
	
	// returns HitLocation FVector from linetrace through crosshair
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	// returns the look vector hit location
	bool GetLookVectorHitLocation(FVector2D ScreenLocation, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;
};
