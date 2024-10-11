// TankAIController.h
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class TOONTANKS_API ATankAIController : public AAIController
{
    GENERATED_BODY()


public:
     ATankAIController();
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

private:
    void MoveInCardinalDirection();
    void ChangeDirectionIfColliding();
    void FindRandomLocation();

    FVector CurrentDirection;
    FVector TargetLocation;
    float MoveInterval;
    float TimeSinceLastMove;
    float Speed;

    TArray<FVector> Directions;
    class UNavigationSystemV1* NavSystem;
};