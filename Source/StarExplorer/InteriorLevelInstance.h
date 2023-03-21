// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelInstance/LevelInstanceActor.h"
#include "InteriorLevelInstance.generated.h"

/**
 * 
 */
UCLASS()
class STAREXPLORER_API AInteriorLevelInstance : public ALevelInstance
{
	GENERATED_BODY()

public:
	AInteriorLevelInstance();

	USceneComponent* GetPlayerStartLocation() const { return PlayerStartLocation; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "Interior")
	USceneComponent* PlayerStartLocation;
	
};
