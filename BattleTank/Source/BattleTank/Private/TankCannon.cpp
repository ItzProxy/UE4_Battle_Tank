// Fill out your copyright notice in the Description page of Project Settings.

#include "TankCannon.h"

void UTankCannon::Elevate(float RelativeSpeed) {
	//UE_LOG(LogTemp, Warning, TEXT("Forward Declaration of UTankCannon and using Elevate"));
	//RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	UE_LOG(LogTemp, Warning, TEXT("Elevating to: %f"), RelativeSpeed);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);
	//UE_LOG(LogTemp, Warning, TEXT("Elevating to: %f"), ClampedElevation);
	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}