// Fill out your copyright notice in the Description page of Project Settings.


#include "FuelDropConvertorTerminal.h"
#include "ExplorerCharacter.h"
#include "BaseSpaceship.h"


void AFuelDropConvertorTerminal::InteractWith(AExplorerCharacter* player)
{
	if (!ship)
	{
		ship = player->GetExplorerShip();
	}
	if (!bInUse && player->GetFuelDrops() > 0)
	{
		bInUse = true;
		player->ChangeFuelDrops(-1);
		GetWorld()->GetTimerManager().SetTimer(RefuelHandle, this, &AFuelDropConvertorTerminal::RefuelShip, 5.f, false);
	}
}

void AFuelDropConvertorTerminal::RefuelShip()
{
	if (ship)
	{
		ship->AddFuel(100);
		
	}
	bInUse = false;
}
