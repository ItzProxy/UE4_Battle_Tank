// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankAIController.h"
#include "Tank.h"

void ABattleTankAIController::BeginPlay() {
	ActorSuper::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIcontroller has nothin"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIcontroller has possessed %s"), *(ControlledTank->GetName()));
	}

	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("!!AIcontroller has not found a player controller"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("!!AIcontroller has found the player %s"), *(PlayerTank->GetName()));
	}
	//UE_LOG(LogTemp, Warning, TEXT("AIcontroller overridden the BeginPlay() from AActor and specified"));
}

void ABattleTankAIController::Tick(float delta)
{
	Super::Tick(delta);
	AimTowardsPlayer();
}

void ABattleTankAIController::AimTowardsPlayer() const
{
	FVector HitLocation;
	if (PlayerTank) {
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		// TODO Fire at targetted location
		ControlledTank->Fire();
	}
}
