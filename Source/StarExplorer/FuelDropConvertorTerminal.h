// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSpaceTerminal.h"
#include "FuelDropConvertorTerminal.generated.h"

/**
 * 
 */
UCLASS()
class STAREXPLORER_API AFuelDropConvertorTerminal : public ABaseSpaceTerminal
{
	GENERATED_BODY()

private:
	virtual void InteractWith(AExplorerCharacter* player) override;

	UPROPERTY(EditDefaultsOnly, Category = "FuelDropTerminal")
	bool bInUse = false;

	void RefuelShip();

	FTimerHandle RefuelHandle;

	UPROPERTY()
	class ABaseSpaceship* ship;
	
};
