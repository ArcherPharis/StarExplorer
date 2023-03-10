// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseSpaceship.generated.h"

UCLASS()
class STAREXPLORER_API ABaseSpaceship : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseSpaceship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Ship")
	class UPhysicsThrusterComponent* GetThrusterComponent() const { return PhysicsThruster; }
	UFUNCTION(BlueprintCallable, Category = "Ship")
	UStaticMeshComponent* GetShipMesh() const { return ShipMesh; }
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Boost();
	void MoveUp(float Value);
	void Elevate(float Value);
	void Thrust(float Value);
	void MoveRight(float Value);
	void Roll(float Value);

	void ChangeShipTorque(float InputValue, float Power, FVector ShipVector);

	UPROPERTY(EditDefaultsOnly, Category = "Ship")
	UStaticMeshComponent* ShipMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Ship")
	class UPhysicsThrusterComponent* PhysicsThruster;
	UPROPERTY(EditDefaultsOnly, Category = "Ship")
	USceneComponent* ShipRoot;
	UPROPERTY(EditDefaultsOnly, Category = "Ship")
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, Category = "Ship")
	class UCameraComponent* Camera;

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
	UPROPERTY(EditDefaultsOnly, Category = "ShipParameters")
	float MaxSpeed = 10000.f;
	UPROPERTY(EditDefaultsOnly, Category = "ShipParameters")
	FVector ForwardVelocity;
	UPROPERTY(EditDefaultsOnly, Category = "ShipParameters")
	float SpeedBuildUpRate = 0.5f;





};
