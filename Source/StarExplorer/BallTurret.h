// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallTurret.generated.h"

UCLASS()
class STAREXPLORER_API ABallTurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Turret")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Turret")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Turret")
	USceneComponent* FiringMuzzleLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Turret")
	float FireRange = 8000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Turret")
	TSubclassOf<class AProjectile> ProjectileClass;

	class ABaseSpaceship* Ship;

	void RotateTurret(FVector LookAtTarget);

	void Fire();
	void CheckFireCondition();

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;

};
