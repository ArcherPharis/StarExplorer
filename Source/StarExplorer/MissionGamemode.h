// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MissionGamemode.generated.h"

/**
 * 
 */
UCLASS()
class STAREXPLORER_API AMissionGamemode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void GoalRingPassed(AActor* Ring);

private:
	UPROPERTY(VisibleAnywhere, Category = "Rings")
	TArray<class AActor*> GoalRings;

	UPROPERTY(VisibleAnywhere, Category = "Rings")
	int RingsToCapture;
	UPROPERTY(VisibleAnywhere, Category = "Rings")
	int RingsCaptured = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Rings")
	TSubclassOf<class URingWidget> RingWidgetClass;

	URingWidget* RingWidget;
	
};
