// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "GoalRing.h"

void AMissionGamemode::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGoalRing::StaticClass(), GoalRings);
	RingsToCapture = GoalRings.Num();
}

void AMissionGamemode::GoalRingPassed(AActor* Ring)
{
	GoalRings.Remove(Ring);
	RingsToCapture -= 1;
}
