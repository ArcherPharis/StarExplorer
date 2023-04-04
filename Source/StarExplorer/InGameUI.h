// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class STAREXPLORER_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetCurrentFuelMeter(float currentValue, float maxValue);
	void SetCurrentIntegrityMeter(float currentValue, float maxValue);


private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* CurrentFuelMeter;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ShipIntegrityMeter;
	
};
