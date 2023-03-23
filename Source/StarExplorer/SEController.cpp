// Fill out your copyright notice in the Description page of Project Settings.


#include "SEController.h"
#include "InGameUI.h"
#include "ExplorerCharacter.h"
#include "BaseSpaceship.h"

void ASEController::SetShip(ABaseSpaceship* ship)
{
	controllingShip = ship;
	controllingShip->onFuelChange.AddDynamic(this, &ASEController::ChangeFuelGauge);

}


void ASEController::BeginPlay()
{
	Super::BeginPlay();
	InGameUI = CreateWidget<UInGameUI>(this,InGameUIClass);

	if (InGameUI)
	{
		InGameUI->AddToViewport();
	}
}

void ASEController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	controllingPlayer = Cast<AExplorerCharacter>(InPawn);
}

void ASEController::ChangeFuelGauge(float current, float max)
{
	if (InGameUI)
	{
		InGameUI->SetCurrentFuelMeter(current, max);
	}
}
