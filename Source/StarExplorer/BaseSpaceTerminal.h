// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractableInterface.h"
#include "BaseSpaceTerminal.generated.h"

UCLASS()
class STAREXPLORER_API ABaseSpaceTerminal : public AActor, public IIInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSpaceTerminal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	virtual void InteractWith(AExplorerCharacter* player) override;

};
