// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actior  died"))
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		
		if(ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
		
	}

}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
	UE_LOG(LogTemp, Warning, TEXT("AToonTanksGameMode::BeginPlay"))

	
}

void AToonTanksGameMode::HandleGameStart()
{
	//TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimeHandle;
		FTimerDelegate PlayerEnabledTimerDelegate = FTimerDelegate::CreateUObject(
		ToonTanksPlayerController,&AToonTanksPlayerController::SetPlayerEnabledState,true
		);
		GetWorldTimerManager().SetTimer(PlayerEnableTimeHandle,
			PlayerEnabledTimerDelegate,
			StartDelay,
			false);

	}
}

	int32 AToonTanksGameMode::GetTargetTowerCount()
	{
		TArray <AActor*> Towers;
		UGameplayStatics::GetAllActorsOfClass(this,ATower::StaticClass(), Towers);
		return Towers.Num();
	}
