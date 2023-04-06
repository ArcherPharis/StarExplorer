// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataFieldWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPercentageComplete);

/**
 * 
 */
UCLASS()
class STAREXPLORER_API UDataFieldWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnPercentageComplete OnPercentageComplete;

	void UpdateProgressBar(float current, float max);

private:
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* CaptureProgressBar;

	
	
};
