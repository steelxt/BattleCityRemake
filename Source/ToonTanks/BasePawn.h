// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"


UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();
	void Fire();

	UPROPERTY( VisibleAnywhere)
	int32 VisibleAnywhereInt = 12;

protected:
	void RotateTurret( const FVector LookAtTarget);

private:
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Components" , meta =(AllowPrivateAccess ="true"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Components" , meta =(AllowPrivateAccess ="true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Components" , meta =(AllowPrivateAccess ="true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category="Components" , meta =(AllowPrivateAccess ="true"))
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

 	UPROPERTY(VisibleAnywhere, Category="Components")
   	class UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<class UParticleSystem>  DeathParticles;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USoundBase>  DeathSound;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<class UCameraShakeBase>  DeathCameraShakeClass;



public:	
	

	

};
