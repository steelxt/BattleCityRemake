// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"


void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{

	APawn* MyPawn  =GetPawn();
	if(MyPawn)
	{
		if (bPlayerEnabled)
		{
			MyPawn->EnableInput(this);
		}
		else
		{
			MyPawn->DisableInput(this);

		}
	}
	bShowMouseCursor = bPlayerEnabled;
}
