// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(FVector & HitLocation, float LaunchSpeed)
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
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //normalize launch vector
		/*
		UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"),
			*AimDirection.ToString()
		);
		*/
		MoveCannonTowardsDirection(AimDirection);
	}

}

void UTankAimingComponent::SetCannonReference(UStaticMeshComponent * CannonToSet)
{
	Cannon = CannonToSet;
}

void UTankAimingComponent::SetTurretReference(UStaticMeshComponent * TurretToSet)
{
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
	UE_LOG(LogTemp, Warning, TEXT("Aim as rotator: %s"), *DeltaRotator.ToString());
}

