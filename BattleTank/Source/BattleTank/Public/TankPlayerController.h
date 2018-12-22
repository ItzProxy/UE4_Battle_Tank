// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define OUT 

#include "Tank.h"
#include "Engine/World.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{

	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
		float CrossHairX = 0.5f;
	UPROPERTY(EditAnywhere)
		float CrossHairY = 0.33f;


public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	ATank* GetControlledBattleTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation);
	bool LookDirection(const FVector& ScreenSize, FVector &WDir);
	void GetViewportSize(int32&, int32&);
};
