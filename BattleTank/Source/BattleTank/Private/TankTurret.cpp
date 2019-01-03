// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::RotateTurret(float RelativeSpeed) {
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	auto RawNewYaw = RelativeRotation.Yaw + RotationChange;
	UE_LOG(LogTemp, Warning, TEXT("curr YAW: %f"), RawNewYaw);
	SetRelativeRotation(FRotator(0, RawNewYaw, 0));
}