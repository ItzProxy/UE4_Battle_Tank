// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankCannon.h"
#include "TankTurret.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{

	//auto CannonLocation = Cannon->GetComponentLocation();
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), 
	//	*GetOwner()->GetName(), 
	//	*HitLocation.ToString(), 
	//	*CannonLocation.ToString()
	//);
	if (!Cannon) { return; }//protect against unreferenced calls to cannon component

	FVector OutLaunchVelocity;
	FVector StartLocation = Cannon->GetSocketLocation(FName("ProjectileStartPoint"));
	//UE_LOG(LogTemp, Warning, TEXT("Projectile Start at %s"), *StartLocation.ToString());

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OUT OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		false
	);
	if(bHaveAimSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //normalize launch vector
		MoveCannonTowardsDirection(AimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f:Fire! Pressed"), Time);
}

void UTankAimingComponent::SetCannonReference(UTankCannon * CannonToSet)
{
	Cannon = CannonToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::MoveCannonTowardsDirection(FVector AimDirection)
{
	//get the difference between current cannon rotation and the aim direction
	auto CannonRotator = Cannon->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - CannonRotator;
	//UE_LOG(LogTemp, Warning, TEXT("Aim as rotator: %s"), *DeltaRotator.ToString());

	Cannon->Elevate(DeltaRotator.Pitch);
	Turret->RotateTurret(DeltaRotator.Yaw);
}

