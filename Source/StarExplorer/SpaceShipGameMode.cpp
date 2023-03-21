// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShipGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ExplorerCharacter.h"
#include "SEController.h"

void ASpaceShipGameMode::BeginPlay()
{
	Super::BeginPlay();
	SetPlayer(Cast<AExplorerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)));
}

void ASpaceShipGameMode::SetPlayer(AExplorerCharacter* playerToSet)
{
	player = playerToSet;
}

