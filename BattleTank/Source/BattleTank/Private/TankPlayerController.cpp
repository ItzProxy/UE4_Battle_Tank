// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledBattleTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player controller has nothin"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player controller has possessed %s"), *(GetControlledBattleTank()->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("Player controller overridden the BeginPlay() from AActor*"));
}

void ATankPlayerController::Tick(float DeltaTime)
{
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledBattleTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledBattleTank()) { return; }

	FVector HitLocation; //OUT parameter;
	if (GetSightRayHitLocation(HitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation)
{
	int32 ViewportSizeX, ViewPortSizeY;
	FVector WDir;
	GetViewportSize(ViewportSizeX, ViewPortSizeY);
	FVector ScreenSize = FVector(ViewportSizeX, ViewPortSizeY,0);
	HitLocation = FVector(ViewportSizeX*CrossHairX, ViewPortSizeY*CrossHairY, 0.f);
	//De-project
	if (LookDirection(ScreenSize, WDir)) {
		UE_LOG(LogTemp, Warning, TEXT("World Direction : %s"), *WDir.ToString());
	}
	return true;
}

bool ATankPlayerController::LookDirection(const FVector & ScreenSize, FVector & WDir)
{
	FVector WLoc; //hotpotato
	return DeprojectScreenPositionToWorld(ScreenSize.X, ScreenSize.Y, WLoc, WDir);
}

void ATankPlayerController::GetViewportSize(int32 & X, int32 & Y)
{
	if (IsLocalController()) {
		GetViewportSize(OUT X, OUT Y);
	}
}

