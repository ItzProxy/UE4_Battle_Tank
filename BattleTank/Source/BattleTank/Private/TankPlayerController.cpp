// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledBattleTank() const {
	return Cast<ATank>(GetPawn());
}

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

}
