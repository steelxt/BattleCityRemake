// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "TankAIController.h"



ATank::ATank()
{	
}
// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	/*if(Cast<ATankAIController>(GetController()) )
	{
		Cast<ATankAIController>(GetController())->RandomMovement();
	}*/

}
// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (TankPlayerController = Cast<APlayerController>( GetController()))
	{

			if (UEnhancedInputLocalPlayerSubsystem *InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(TankPlayerController->GetLocalPlayer()))
			{
				if (InputMapping)
				{
					UE_LOG(LogTemp, Warning, TEXT(" passed InputMapping"));

					InputSystem->AddMappingContext(InputMapping, 0);
				}
			}

		if (UEnhancedInputComponent *Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
		{
			UE_LOG(LogTemp, Warning, TEXT(" setup input"));
			if(InputMoveForward)
			{
				Input->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &ATank::MoveForwardEvent);
			}

			if (InputFire)
			{

					Input->BindAction(InputFire, ETriggerEvent::Triggered, this, &ATank::FireEvent);

			}
			//Input->BindAction(InputLookUp, ETriggerEvent::Triggered, this, &AShooterCharacter::LookUp);
			//Input->BindAction(InputJump, ETriggerEvent::Triggered, this, &AShooterCharacter::HandleJump);


		}
	}

}


void ATank::MoveForwardEvent(const FInputActionValue &Instance)
{
	const FVector2D MovementVector =  Instance.Get<FVector2D>();

	AddActorWorldOffset(GetActorForwardVector() * Speed * GetWorld()->DeltaTimeSeconds, true);
	if (MovementVector.X != 0.0f)
    {
        LastDirectionInput = FVector2D(MovementVector.X, 0.0f);  // Prioritize X-axis input if it exists
    }
    else if (MovementVector.Y != 0.0f)
    {
        LastDirectionInput = FVector2D(0.0f, MovementVector.Y);  // Prioritize Y-axis input if no X input
    }
	RotateTankInstantly(LastDirectionInput.Y, LastDirectionInput.X);
	//RotateTank(MovementVector.Y, MovementVector.X, GetWorld()->DeltaTimeSeconds);

	UE_LOG(LogTemp, Warning, TEXT("Value: Y %f X %f, speed = %f"), MovementVector.Y, MovementVector.X, Speed);
}


void ATank::MoveForwardEventTest(const FInputActionValue &Instance)
{
	const FVector2D MovementVector =  Instance.Get<FVector2D>();
	
	UE_LOG(LogTemp, Warning, TEXT("Value: Y %f X %f, speed = %f"), MovementVector.Y, MovementVector.X, Speed);
}

void ATank::FireEvent(const FInputActionValue &Instance)
{
	//UE_LOG(LogTemp, Warning, TEXT(" from fire event"));

	Fire();
}
void ATank::Move(const float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("move Value: %f"), Value  )
	FVector DeltaLocation = FVector::ZeroVector;
	float  ValueOffset = Value * UGameplayStatics::GetWorldDeltaSeconds(this)* Speed;
	//UE_LOG(LogTemp, Warning, TEXT("move Value offset: %f"), ValueOffset  )
	DeltaLocation.X = ValueOffset;
	AddActorLocalOffset(DeltaLocation);		
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(TankPlayerController)
	{
		FHitResult HitResult;
	}
}

void ATank::HandleDestruction() {
	Super::HandleDestruction();
	if(Cast<ATankAIController>(GetController()) )
	{
		Destroy();
	}else
	{
			SetActorHiddenInGame(true);
			SetActorTickEnabled(true);
	}
	bAlive = false;
}


void ATank::Turn(const float Value)
{
	FRotator DeltaRotator = FRotator::ZeroRotator;
	DeltaRotator.Yaw = Value;//  UGameplayStatics::GetWorldDeltaSeconds(this)* TurnRate;
	AddActorLocalRotation(DeltaRotator, false);
}

void ATank::RotateTankInstantly(float XInput, float YInput)
{
    if (XInput == 0.0f && YInput == 0.0f)
    {
        return; // No input, don't rotate
    }

    // Determine the new rotation based on the input direction
    FRotator NewRotation;

    if (XInput > 0)
    {
        // Move Right -> Face 0 degrees
        NewRotation = FRotator(0.0f, 0.0f, 0.0f);
    }
    else if (XInput < 0)
    {
        // Move Left -> Face 180 degrees
        NewRotation = FRotator(0.0f, 180.0f, 0.0f);
    }
    else if (YInput > 0)
    {
        // Move Up -> Face 90 degrees
        NewRotation = FRotator(0.0f, 90.0f, 0.0f);
    }
    else if (YInput < 0)
    {
        // Move Down -> Face -90 degrees (or 270 degrees)
        NewRotation = FRotator(0.0f, -90.0f, 0.0f);
    }

    // Instantly apply the new rotation to the tank
    SetActorRotation(NewRotation);
}

void ATank::RotateTank(float XInput, float YInput, float DeltaTime)
{
    if (XInput == 0.0f && YInput == 0.0f)
    {
        return; // No input, don't rotate
    }

    // Calculate the desired direction based on the movement input
    FVector DesiredDirection = FVector(XInput, YInput, 0.0f).GetSafeNormal();

    // Calculate the target rotation from the desired direction
    FRotator TargetRotation = DesiredDirection.Rotation();

    // Interpolate smoothly from the current rotation to the target rotation
    FRotator CurrentRotation = GetActorRotation();
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, TurnRate);

    // Apply the new rotation to the tank
    SetActorRotation(NewRotation);
}

