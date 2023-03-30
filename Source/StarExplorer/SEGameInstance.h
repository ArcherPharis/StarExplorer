// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SEGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class STAREXPLORER_API USEGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void SetShipFuel(float fuel);
	float GetShipFuel() const { return ShipFuel; }

private:
	float ShipFuel;
	
};
