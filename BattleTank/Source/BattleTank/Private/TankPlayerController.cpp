// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"

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
	Super::Tick(DeltaTime);
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
		GetControlledBattleTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	int32 ViewportSizeX, ViewPortSizeY;
	FVector LookDirection;
	//Get the viewport from the client of the player controlled tank
	GetViewportSize(ViewportSizeX, ViewPortSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairX, ViewPortSizeY*CrossHairY);
	//HitLocation = FVector(ScreenSize.X*CrossHairX, ScreenSize.Y*CrossHairY, 0.f);
	//De-project

	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("World Direction : %s"), *WDir.ToString());
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(const FVector2D & ScreenLocation, FVector & WDir) const
{
	FVector WLoc; //hotpotato
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WLoc, WDir);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDir, FVector & HitLocation) const
{
	FHitResult HitResult;
	auto StartLoc = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLoc + (LookDir * LineTraceDistance);

	if (GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		StartLoc,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	)) {
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}


