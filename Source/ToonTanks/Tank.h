// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	TObjectPtr<APlayerController> GetTankPlayerController() const {
		return TankPlayerController;
	};

	bool bAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	/*UPROPERTY( VisibleAnywhere, Category="Components")
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY( VisibleAnywhere, Category="Components")
	TObjectPtr<class UCameraComponent> Camera;*/
	UPROPERTY( EditAnywhere, Category="Movement")
	float Speed = 200.F;
	UPROPERTY( EditAnywhere, Category="Movement")
	float TurnRate = 45.F;
	UPROPERTY(EditAnywhere,Category = "Enhanced Input")
	TObjectPtr<class UInputAction> InputMoveForward;
	UPROPERTY(EditAnywhere,Category = "Enhanced Input")
	TObjectPtr<class UInputAction> InputFire;


	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	TObjectPtr<class UInputMappingContext> InputMapping;

	TObjectPtr<APlayerController> TankPlayerController;
	FVector2D LastDirectionInput;
//function section
	void MoveForwardEvent(const struct FInputActionValue &Instance);
	void MoveForwardEventTest(const struct FInputActionValue &Instance);
    void FireEvent(const struct FInputActionValue &Instance);


  
	
	
	
public:
	void Move(const float Value);
	void Turn(const float Value); 
	void RotateTank(float XInput, float YInput, float DeltaTime);
	void RotateTankInstantly(float XInput, float YInput);
	
};
