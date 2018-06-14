// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "public/Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h" // must be last include

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATank* GetAIControlledTank() const;
	ATank* GetPlayerTank() const;

	// called once on beginplay
	virtual void BeginPlay() override;
	
	// called every frame
	virtual void Tick(float DeltaTime) override;
	
};
