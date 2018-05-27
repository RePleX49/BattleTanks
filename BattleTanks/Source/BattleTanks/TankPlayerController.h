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

public:
	ATank* GetControlledTank() const;
	
	// called only once when begin play
	virtual void BeginPlay() override;

	// called on every frame
	virtual void Tick(float DeltaTime) override;

	// aims barrel towards crosshair in 3D space
	void AimTowardsCrosshair();
	
};
