// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "Components/ProgressBar.h"
#include "BeginMissionWidget.h"

void UInGameUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInGameUI::SetCurrentFuelMeter(float currentValue, float maxValue)
{
	CurrentFuelMeter->SetPercent(currentValue / maxValue);
}

void UInGameUI::SetCurrentIntegrityMeter(float currentValue, float maxValue)
{
	ShipIntegrityMeter->SetPercent(currentValue / maxValue);
}

