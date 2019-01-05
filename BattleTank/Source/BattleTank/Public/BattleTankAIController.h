// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "BattleTankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ABattleTankAIController : public AAIController
{
private:
	GENERATED_BODY()
	typedef AActor ActorSuper;

	ATank* PlayerTank = nullptr;
	ATank* ControlledTank = nullptr;
	void AimTowardsPlayer() const;

public:
	void BeginPlay() override;
	void Tick(float delta) override;


};
