// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RingWidget.generated.h"

/**
 * 
 */
UCLASS()
class STAREXPLORER_API URingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetRingsRemainingText(int amount);
	void SetTotalRingsText(int amount);


private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RingsRemainingText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RingsTotalText;
	
};
