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
	void Elevate(float DegreesPerSecond);

private:
	UPROPERTY(EditAnywhere)
		float MaxDegreePerSecond = 20.f; //Max degrees can be per second
	UPROPERTY(EditAnywhere)
		float MaxElevation = 60.f; //Max degrees can be
	UPROPERTY(EditAnywhere)
		float MinElevation = -15.f; //Min degrees can be
};
