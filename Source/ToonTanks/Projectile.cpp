// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraShakeBase.h"




// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>( TEXT("Projectile Movement Component"));
	ProjectileMovementComp->MaxSpeed = 1300.f;
	ProjectileMovementComp->InitialSpeed = 1300.f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>( TEXT("Trail Particle Component"));
	TrailParticles->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this,&AProjectile::OnHit );	

	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,  FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit"));
	/*UE_LOG(LogTemp, Warning, TEXT("HitComp:  %s"), *HitComp->GetName());
	UE_LOG(LogTemp, Warning, TEXT("OtherActor:  %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("OtherComp:  %s"), *OtherComp->GetName());*/
	auto MyOwner = GetOwner();
	if(MyOwner!= nullptr)
	{
		auto MyOwnerInstigator = MyOwner->GetInstigatorController();
		auto DamageTypeClass = UDamageType::StaticClass();
		if(OtherActor&& OtherActor != this && OtherActor!= MyOwner)
		{
			UE_LOG(LogTemp, Warning, TEXT("Call apply damage"));
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);			
		}			
		UGameplayStatics::SpawnEmitterAtLocation(this,HitParticles, GetActorLocation(), GetActorRotation() );
		if(HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}

	}
	if(HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}

	Destroy();

}


