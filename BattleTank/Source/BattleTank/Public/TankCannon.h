// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankCannon.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankCannon : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 5.0f; //Max degrees can be per second
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevation = 60.f; //Max degrees can be
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevation = 0.f; //Min degrees can be
};
