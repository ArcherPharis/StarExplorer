// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SEController.generated.h"

/**
 * 
 */
UCLASS()
class STAREXPLORER_API ASEController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetShip(class ABaseSpaceship* ship);

	void ShowBeginMissionUI();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UInGameUI> InGameUIClass;

	UPROPERTY()
	UInGameUI* InGameUI;

	class ABaseSpaceship* controllingShip;
	class AExplorerCharacter* controllingPlayer;



	UFUNCTION()
	void ChangeFuelGauge(float current, float max);
	
};
