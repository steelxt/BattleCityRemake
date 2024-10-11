// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Camera/CameraShakeBase.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>( TEXT("capsule collider"));
	RootComponent = CapsuleComp;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
    MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("CharacterMovement"));
	MovementComponent->UpdatedComponent = CapsuleComp;

	}

void ABasePawn::HandleDestruction()
{
	if(DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,DeathParticles, GetActorLocation(), GetActorRotation() );
	}

	if(DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

	if(DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}


}
void ABasePawn::RotateTurret(const FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = 	FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation,UGameplayStatics::GetWorldDeltaSeconds(this),15.f));
}

void ABasePawn::Fire()
{
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint ->GetComponentLocation();
	FRotator ProjectileSpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
	//DrawDebugSphere(GetWorld(),ProjectileSpawnPointLocation, 20.f, 12, FColor::Green, false, 3.f);
	if(ProjectileClass)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,ProjectileSpawnPointLocation, ProjectileSpawnRotation);
		Projectile->SetOwner(this);
	}

}





