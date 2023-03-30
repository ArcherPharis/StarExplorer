// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "IInteractableInterface.h"
#include "BaseSpaceship.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFuelChange, float, currentValue, float, maxValue);

UCLASS()
class STAREXPLORER_API ABaseSpaceship : public APawn, public IIInteractableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseSpaceship();

	FOnFuelChange onFuelChange;

	void AddFuel(float amount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MaxSpeedBoost();

	UFUNCTION(BlueprintCallable, Category = "Ship")
	class UPhysicsThrusterComponent* GetThrusterComponent() const { return PhysicsThruster; }
	UFUNCTION(BlueprintCallable, Category = "Ship")
	UStaticMeshComponent* GetShipMesh() const { return ShipMesh; }
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void SetShipInterior(class AInteriorLevelInstance* shipInt);

	void SetSpeed(float newSpeed);

	class ASEController* GetSpaceController() const { return spaceController; }

private:
	void Boost();
	void MoveUp(float Value);
	void Elevate(float Value);
	void Thrust(float Value);
	void MoveRight(float Value);
	void Roll(float Value);
	void SpawnInterior();
	void StopPiloting();
	void Fire();

	virtual void InteractWith(AExplorerCharacter* player) override;

	void ChangeShipTorque(float InputValue, float Power, FVector ShipVector);

	UPROPERTY(EditDefaultsOnly, Category = "Ship")
	UStaticMeshComponent* ShipMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Ship")
	USceneComponent* ProjectileLaunchMuzzle;
	UPROPERTY(EditDefaultsOnly, Category = "Ship")
	class UPhysicsThrusterComponent* PhysicsThruster;
	UPROPERTY(EditDefaultsOnly, Category = "Ship")
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, Category = "Ship")
	class UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly, Category = "Ship")
	TSubclassOf<class AInteriorLevelInstance> ShipInteriorClass;
	UPROPERTY(VisibleAnywhere, Category = "Ship")
	AInteriorLevelInstance* ShipInterior;
	UPROPERTY()
	class ASpaceShipGameMode* gameMode;
	UPROPERTY()
	class AExplorerCharacter* playerExplorer;
	UPROPERTY()
	ASEController* spaceController;

	UPROPERTY(EditDefaultsOnly, Category = "Ship")
	TSubclassOf<class AProjectile> ProjectileClass;


	UPROPERTY(EditDefaultsOnly, Category = "ShipParameters")
	float MaxFuel = 1000.f;
	UPROPERTY(EditAnywhere, Category = "ShipParameters")
	float CurrentFuel = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "ShipParameters")
	float LiftPower = 500.f;
	UPROPERTY(EditDefaultsOnly, Category = "ShipParameters")
	float PitchPower = 40.f;
	UPROPERTY(EditDefaultsOnly, Category = "ShipParameters")
	float RollingPower = 100.f;
	UPROPERTY(EditDefaultsOnly, Category = "ShipParameters")
	float TurnPower = 200.f;
	UPROPERTY(EditDefaultsOnly, Category = "ShipParameters")
	float Speed = 0.f;
	UPROPERTY(EditAnywhere, Category = "ShipParameters")
	float MaxSpeed = 10000.f;
	UPROPERTY(EditDefaultsOnly, Category = "ShipParameters")
	FVector ForwardVelocity;
	UPROPERTY(EditDefaultsOnly, Category = "ShipParameters")
	float SpeedBuildUpRate = 0.5f;

	void ReturnToNormalSpeed();
	bool bCurrentlyBoosted = false;
	float BoostTime = 2.5f;
	FTimerHandle SpeedReturnTimer;

	UPROPERTY()
	class USEGameInstance* Instance;
	





};
