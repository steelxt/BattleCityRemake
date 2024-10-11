// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	ToonTanksGameMode =Cast<AToonTanksGameMode>( UGameplayStatics::GetGameMode( this));
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay ToonTanksGameMode null= %hs"), (ToonTanksGameMode == nullptr ? "true" : "false"));

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken( AActor* DamagedActor, float Damage ,
	const UDamageType* DamageType, class AController* Instigator,  AActor* DamageCauser )
{			
	Health -= Damage;

	if(Damage>0&&Health<=0.f && ToonTanksGameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("Health:  %f"), Health)

	    ToonTanksGameMode->ActorDied(DamagedActor);

	}
}
