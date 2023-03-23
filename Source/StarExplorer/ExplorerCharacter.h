// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ExplorerCharacter.generated.h"

UCLASS()
class STAREXPLORER_API AExplorerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExplorerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetExplorerShip(class ABaseSpaceship* myNewShip);

	ABaseSpaceship* GetExplorerShip() const { return MySpaceship; }

	void ChangeFuelDrops(int amount);
	int GetFuelDrops() const { return FuelDrops; }

private:
	UPROPERTY(EditAnywhere, Category = "Explorer")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, Category = "Explorer")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category = "Explorer")
	float GrabRange = 200.f;

	UPROPERTY(EditAnywhere, Category = "FuelDrops")
	int FuelDrops = 1;
	UPROPERTY(EditDefaultsOnly, Category = "FuelDrops")
	int MaxFuelDrops = 100;

	UPROPERTY()
	ABaseSpaceship* MySpaceship;

	void Interact();
};
