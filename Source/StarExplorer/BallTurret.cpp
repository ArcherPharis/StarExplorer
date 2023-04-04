// Fill out your copyright notice in the Description page of Project Settings.


#include "BallTurret.h"
#include "BaseSpaceship.h"
#include "Projectile.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABallTurret::ABallTurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	SetRootComponent(BodyMesh);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);
	FiringMuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	FiringMuzzleLocation->SetupAttachment(TurretMesh);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));


}

// Called when the game starts or when spawned
void ABallTurret::BeginPlay()
{
	Super::BeginPlay();
	Ship = Cast<ABaseSpaceship>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ABallTurret::CheckFireCondition, FireRate, true);
	HealthComponent->OnDeath.AddDynamic(this, &ABallTurret::OnDead);

}

// Called every frame
void ABallTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Ship)
	{
		float Distance = FVector::Dist(GetActorLocation(), Ship->GetActorLocation());
		if (Distance <= FireRange)
		{
			RotateTurret(Ship->GetActorLocation());
		}
	}

}

void ABallTurret::RotateTurret(FVector LookAtTarget)
{
	FVector Target = LookAtTarget - GetActorLocation();
	FRotator LookAtRotation = Target.Rotation();
	SetActorRotation(LookAtRotation);
}

void ABallTurret::Fire()
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, FiringMuzzleLocation->GetComponentTransform());
}

void ABallTurret::CheckFireCondition()
{
	if (Ship)
	{
		float Distance = FVector::Dist(GetActorLocation(), Ship->GetActorLocation());
		if (Distance <= FireRange)
		{
			Fire();
		}
	}
}

