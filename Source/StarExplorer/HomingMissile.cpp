// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingMissile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AHomingMissile::AHomingMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AHomingMissile::SetHomingTarget(AActor* Target)
{
	GetProjectileMovementComponent()->HomingTargetComponent = Target->GetRootComponent();
}

// Called when the game starts or when spawned
void AHomingMissile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHomingMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
