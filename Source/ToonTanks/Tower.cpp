// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
		if(InfireRange())
		{
			// if in range rotate the tower
			RotateTurret(Tank->GetActorLocation());
		}
	
	
} 
void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}


void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank> (UGameplayStatics::GetPlayerPawn(this,0));
	GetWorldTimerManager().SetTimer(FireRateTimeHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	
	if(Tank)
	{
		if(Tank->bAlive&& InfireRange() )
		{
			Fire();
		}
	}
	
}
bool ATower::InfireRange()
{
	if(Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		return (Distance <= FireRange);
		
	}
	return false;
}
