// Fill out your copyright notice in the Description page of Project Settings.


#include "DataFieldWidget.h"
#include "Components/ProgressBar.h"

void UDataFieldWidget::UpdateProgressBar(float current, float max)
{
	CaptureProgressBar->SetPercent(current / max);

	if (CaptureProgressBar->GetPercent() >= 1.f)
	{
		OnPercentageComplete.Broadcast();
	}
}
