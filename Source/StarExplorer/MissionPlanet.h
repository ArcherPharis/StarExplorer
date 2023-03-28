// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissionPlanet.generated.h"

UCLASS()
class STAREXPLORER_API AMissionPlanet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissionPlanet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Mission Planet")
	UStaticMeshComponent* MeshComp;
	UPROPERTY(EditDefaultsOnly, Category = "Mission Planet")
	class USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly,Category = "Mission Planet")
	TSoftObjectPtr<UWorld>PlanetLevel;

	UPROPERTY(EditDefaultsOnly, Category = "Mission Planet")
	TSubclassOf<class UBeginMissionWidget> MissionWidgetClass;
	UBeginMissionWidget* MissionWidget;

	class ASEController* cont;
	class ABaseSpaceship* ship;

	UFUNCTION()
	void QueryMissionStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void BeginMission();

	UFUNCTION()
	void CancelQuery();
};
