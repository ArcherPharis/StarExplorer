// Fill out your copyright notice in the Description page of Project Settings.


#include "SEController.h"
#include "InGameUI.h"
#include "ExplorerCharacter.h"
#include "HealthComponent.h"
#include "BaseSpaceship.h"

void ASEController::SetShip(ABaseSpaceship* ship)
{
	controllingShip = ship;
	controllingShip->onFuelChange.AddDynamic(this, &ASEController::ChangeFuelGauge);
	controllingShip->GetHealthComponent()->OnHealthChange.AddDynamic(this, &ASEController::ChangeIntegrityMeter);

}



void ASEController::SetIsInGameplay(bool inGameplay)
{
	bIsInGameplay = inGameplay;
}

void ASEController::BeginPlay()
{
	Super::BeginPlay();
	InGameUI = CreateWidget<UInGameUI>(this,InGameUIClass);
	FInputModeGameOnly inputMode;
	//inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(inputMode);
	
	if (InGameUI)
	{
		InGameUI->AddToViewport();
	}


}

void ASEController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bIsInGameplay)
	{
		FVector2D ScreenSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

		SetMouseLocation(ScreenSize.X / 2, ScreenSize.Y / 2);
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

void ASEController::ChangeIntegrityMeter(float current, float max)
{
	if (InGameUI)
	{
		InGameUI->SetCurrentIntegrityMeter(current, max);
	}
}
