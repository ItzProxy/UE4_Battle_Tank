// Fill out your copyright notice in the Description page of Project Settings.

#include "TankCannon.h"

void UTankCannon::Elevate(float RelativeSpeed) {
	//UE_LOG(LogTemp, Warning, TEXT("Forward Declaration of UTankCannon and using Elevate"));
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->GetDeltaSeconds();
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto ClampedElevation = FMath::Clamp(RawNewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}