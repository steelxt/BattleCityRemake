// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GridAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AGridAIController : public AAIController
{
	GENERATED_BODY()
	
public:
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;
   	virtual void OnPossess(APawn *InPawn) override;

private:
    void MoveInRandomDirection();
    void ChangeDirectionIfColliding();
    void Shoot();

    FVector CurrentDirection;
    float MoveInterval;
    float TimeSinceLastMove;
    UPROPERTY(EditAnywhere)
	float Speed = 200.f;
    UPROPERTY(EditAnywhere)
	float RepeatTimeDelay = 5.f;
	FTimerHandle RepeatTimer;
	
};
