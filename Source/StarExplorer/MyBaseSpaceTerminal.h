// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSpaceTerminal.h"
#include "MyBaseSpaceTerminal.generated.h"

/**
 * 
 */
UCLASS()
class STAREXPLORER_API AMyBaseSpaceTerminal : public ABaseSpaceTerminal
{
	GENERATED_BODY()

private:
	//named it mybasespacetermina (DOH!) this is to switch to the ship control
	virtual void InteractWith(AExplorerCharacter* player) override;
	
};
