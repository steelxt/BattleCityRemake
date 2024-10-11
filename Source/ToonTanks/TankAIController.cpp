#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"

ATankAIController::ATankAIController()
{
    Directions.Add(FVector(1, 0, 0));   // Move right
    Directions.Add(FVector(-1, 0, 0));  // Move left
    Directions.Add(FVector(0, 1, 0));   // Move forward
    Directions.Add(FVector(0, -1, 0));  // Move backward
}

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    MoveInterval = 1.0f; // Move every second
    TimeSinceLastMove = 0.0f;
    Speed = 300.0f; // Units per second, adjustable speed

    NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    FindRandomLocation();  // Get initial target location
}


void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TimeSinceLastMove += DeltaTime;
    if (TimeSinceLastMove >= MoveInterval)
    {
        TimeSinceLastMove = 0.0f;
        ChangeDirectionIfColliding();  // Check if colliding before moving
    }

    // Move towards the target location (one step in cardinal direction at a time)
    FVector PawnLocation = GetPawn()->GetActorLocation();
    FVector DirectionToTarget = (TargetLocation - PawnLocation).GetSafeNormal();

    FVector AdjustedDirection;
    
    if (FMath::Abs(DirectionToTarget.X) > FMath::Abs(DirectionToTarget.Y)) {
        AdjustedDirection = FVector(FMath::Sign(DirectionToTarget.X), 0, 0);  // Move along X (east/west)
    } else {
        AdjustedDirection = FVector(0, FMath::Sign(DirectionToTarget.Y), 0);  // Move along Y (north/south)
    }

    GetPawn()->AddActorWorldOffset(AdjustedDirection * Speed * DeltaTime);

    // Check if we're close enough to the target location and find a new one
    if (FVector::DistSquared(PawnLocation, TargetLocation) < FMath::Square(100.0f)) {
        FindRandomLocation();  // Recalculate random location
    }
}

void ATankAIController::MoveInCardinalDirection()
{
    int32 DirectionIndex = FMath::RandRange(0, Directions.Num() - 1);
    CurrentDirection = Directions[DirectionIndex];

    // Set the rotation based on the chosen direction
    GetPawn()->SetActorRotation(CurrentDirection.Rotation());
}

void ATankAIController::ChangeDirectionIfColliding()
{
    FVector Start = GetPawn()->GetActorLocation();
    FVector End = Start + (CurrentDirection * 100.0f);  // Look ahead in the current direction
    
    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetPawn());
    
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
    
    if (bHit)
    {
        // If we hit an obstacle, choose a new random direction
        MoveInCardinalDirection();
    }

    // Debug line for visualizing the line trace
    DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Red : FColor::Green, false, 1.0f, 0, 5.0f);
}

void ATankAIController::FindRandomLocation()
{
    if (!NavSystem) return;

    FVector Origin = GetPawn()->GetActorLocation();
    FNavLocation RandomPoint;

    // Get a random navigable point within 1000 units
    NavSystem->GetRandomPointInNavigableRadius(Origin, 1000.0f, RandomPoint);

    // Snap the random point to a cardinal direction from the current location
    TargetLocation = RandomPoint;

    UE_LOG(LogTemp, Warning, TEXT("New Target Location: %s"), *TargetLocation.ToString());
}
