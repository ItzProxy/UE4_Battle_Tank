// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankAIController.h"

void ABattleTankAIController::BeginPlay() {
	ActorSuper::BeginPlay();
	auto ControlledTank = GetControlledBattleTank();
	auto PlayerTank = GetPlayerTank();

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
	//UE_LOG(LogTemp, Warning, TEXT("Works"));
}

ATank * ABattleTankAIController::GetControlledBattleTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ABattleTankAIController::GetPlayerTank() const
{
	/*
	auto APlayerArray = GetWorld()->GetGameState()->PlayerArray;
	auto AOwner = GetOwner();
	for (APlayerState* player : APlayerArray) {
		if(player)
		UE_LOG(LogTemp, Warning, TEXT("%s found the player controlled: %s"),*AOwner->GetName())
	}
	*/
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return PlayerPawn ? Cast<ATank>(PlayerPawn) : nullptr;
}
