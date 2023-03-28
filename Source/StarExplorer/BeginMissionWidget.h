// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BeginMissionWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConfirm);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCancel);


/**
 * 
 */
UCLASS()
class STAREXPLORER_API UBeginMissionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void StartMission();

	UFUNCTION()
	void Cancel();

	FOnConfirm onConfirm;
	FOnCancel onCancel;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* BeginMissionButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	
};
