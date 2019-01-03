// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetCannonReference(UTankCannon * CannonToSet)
{
	Cannon = CannonToSet; //local reference
	TankAimingComponent->SetCannonReference(CannonToSet);
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f:Fire! Pressed"), Time);

	if (!Cannon) { return; }
	
	//Spawn projectile at socket location
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBP,
		Cannon->GetSocketLocation(FName("ProjectileStartPoint")),
		Cannon->GetSocketRotation(FName("ProjectileStartPoint"))
	);
	Projectile->LaunchProjectile(LaunchSpeed);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

