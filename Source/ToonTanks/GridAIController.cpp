// Fill out your copyright notice in the Description page of Project Settings.


#include "GridAIController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Tank.h"


void AGridAIController::BeginPlay()
{    
    Super::BeginPlay();
    APawn* ControlledPawn = GetPawn();

    if(ControlledPawn!= nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("AGridAIController::BeginPlay() pawn is  ok"));
        GetWorldTimerManager().SetTimer(RepeatTimer,this, &AGridAIController::Shoot,RepeatTimeDelay, true);

    }

    MoveInterval = 0.2f; // Move every second
    TimeSinceLastMove = 0.0f;
    MoveInRandomDirection();
}


void AGridAIController::OnPossess(APawn *InPawn)
{
    UE_LOG(LogTemp, Warning, TEXT("AGridAIController::OnPossess"))
    Super::OnPossess(InPawn);
    SetPawn(InPawn);

}
void AGridAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

  
    TimeSinceLastMove = 0.0f;
    ChangeDirectionIfColliding();
    if( GetPawn())
    {
        
        GetPawn()-> AddActorWorldOffset(GetPawn()->GetActorForwardVector() * Speed * DeltaTime);

        //  GetPawn()->AddActorWorldOffset(CurrentDirection * 100.0f,true); // Move 100 units in the current direction

    }
 
}
void AGridAIController::Shoot()
{
    UE_LOG(LogTemp, Warning, TEXT("Shoot...."));

    ATank *Tank  = Cast<ATank>(GetPawn());
    if(Tank != nullptr)
    {
        Tank->Fire();
    }
}

void AGridAIController::MoveInRandomDirection()
{
    int32 Direction = FMath::RandRange(0, 3);
    switch (Direction)
    {
    case 0: CurrentDirection = FVector(1, 0, 0); break; // Move right
    case 1: CurrentDirection = FVector(-1, 0, 0); break; // Move left
    case 2: CurrentDirection = FVector(0, 1, 0); break; // Move forward
    case 3: CurrentDirection = FVector(0, -1, 0); break; // Move backward
    }
    if( GetPawn())
        GetPawn()->SetActorRotation(CurrentDirection.Rotation());
}

void AGridAIController::ChangeDirectionIfColliding()
{

    if( GetPawn())
    {
        FVector Start = GetPawn()->GetActorLocation();
        FVector End = Start + (CurrentDirection * 150.0f);
        FHitResult HitResult;

        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(GetPawn());

        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
        if (bHit)
        {
            MoveInRandomDirection();
        }
    }
}
