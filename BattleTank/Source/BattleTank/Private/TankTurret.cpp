// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::RotateTurret(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	//auto RawNewYaw = GetComponentTransform().GetRotation().Z +  + RotationChange;
	auto RawNewYaw = RelativeRotation.Yaw + RotationChange;
	//RawNewYaw = FMath::ClampAngle(RawNewYaw, 360, -360);
	SetRelativeRotation(FRotator(0, RawNewYaw, 0));

}