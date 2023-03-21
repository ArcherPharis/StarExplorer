// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBaseSpaceTerminal.h"
#include "ExplorerCharacter.h"
#include "BaseSpaceship.h"

void AMyBaseSpaceTerminal::InteractWith(AExplorerCharacter* player)
{
	//player knows of the ship now, work your magic.
	APlayerController* cont = Cast<APlayerController>(player->GetOwner());
	cont->UnPossess();
	cont->Possess(player->GetExplorerShip());
}
