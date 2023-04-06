// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataFieldGoal.generated.h"

UCLASS()
class STAREXPLORER_API ADataFieldGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADataFieldGoal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataFieldGoal")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "DataFieldGoal")
	class USphereComponent* HitSphere;

	UPROPERTY(EditDefaultsOnly, Category = "Rings")
	TSubclassOf<class UDataFieldWidget> DataFieldWidgetClass;

	UDataFieldWidget* DataFieldWidget;

	bool bCurrentlyCapturing = false;

	float CurrentCapture = 0;
	float MaxCaptureAmount = 100;
	UPROPERTY(EditDefaultsOnly)
	float ProgressClimbAmount = 0.2f;

	UFUNCTION()
	void CaptureComplete();

	UFUNCTION()
	void AttemptCapture(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void LeaveCaptureRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
