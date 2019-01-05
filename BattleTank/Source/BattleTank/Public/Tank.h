// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankCannon.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class UTankAimingComponent;
class UTankCannon;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:

	ATank* ControlledTank  = nullptr;
	ATank* PlayerTank = nullptr;

	float PrevTime = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float FireRate = 0.33f; //starting value of 1000 ms/s
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 4000; //starting value of 1000 ms/s
	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBP;

	//Cannon reference
	UTankCannon* Cannon = nullptr;
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent* TankAimingComponent = nullptr;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetCannonReference(UTankCannon* CannonToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Fire();
	void SpawnAndFire();
};
