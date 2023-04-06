// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "RingWidget.h"
#include "DataFieldGoal.h"

void AMissionGamemode::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* cont = UGameplayStatics::GetPlayerController(this, 0);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADataFieldGoal::StaticClass(), DataGoals);
	GoalsToCapture = DataGoals.Num();
	if (RingWidgetClass)
	{
		RingWidget = CreateWidget<URingWidget>(cont, RingWidgetClass);
		RingWidget->AddToViewport();
		RingWidget->SetTotalRingsText(GoalsToCapture);
	}
}

void AMissionGamemode::GoalRingPassed(AActor* Ring)
{
	DataGoals.Remove(Ring);
	GoalsCaptured++;
	RingWidget->SetRingsRemainingText(GoalsCaptured);
	Ring->Destroy();
}
