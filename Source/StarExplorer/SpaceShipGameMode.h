// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceShipGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STAREXPLORER_API ASpaceShipGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "SpaceGameMode")
	void SetPlayer(class AExplorerCharacter* playerToSet);


	UFUNCTION(BlueprintCallable, Category = "SpaceGameMode")
	AExplorerCharacter* GetSpacePlayer() const { return player; }


private:
	UPROPERTY(VisibleAnywhere)
	class AExplorerCharacter* player;

};
