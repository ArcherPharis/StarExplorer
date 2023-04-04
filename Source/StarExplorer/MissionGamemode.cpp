// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "RingWidget.h"
#include "GoalRing.h"

void AMissionGamemode::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* cont = UGameplayStatics::GetPlayerController(this, 0);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGoalRing::StaticClass(), GoalRings);
	RingsToCapture = GoalRings.Num();
	if (RingWidgetClass)
	{
		RingWidget = CreateWidget<URingWidget>(cont, RingWidgetClass);
		RingWidget->AddToViewport();
		RingWidget->SetTotalRingsText(RingsToCapture);
	}
}

void AMissionGamemode::GoalRingPassed(AActor* Ring)
{
	GoalRings.Remove(Ring);
	RingsCaptured++;
	RingWidget->SetRingsRemainingText(RingsCaptured);
}
