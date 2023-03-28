// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	HitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	HitSphere->SetupAttachment(RootComponent);
	
}

void AProjectile::SetTarget(FVector Location)
{
	//FVector Direction = Location - GetActorLocation();
	//Direction.Normalize();
	//FRotator Rotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	//SetActorRotation(Rotation);

	FVector CurrentVelocity = ProjectileComponent->Velocity;
	FVector NewVelocity = Location * CurrentVelocity.Size();

	ProjectileComponent->SetVelocityInLocalSpace(NewVelocity);
}


// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

