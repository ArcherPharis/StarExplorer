// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpaceship.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SEController.h"
#include "ExplorerCharacter.h"
#include "Components/WidgetComponent.h"
#include "SpaceShipGameMode.h"
#include "HealthComponent.h"
#include "SEGameInstance.h"
#include "Projectile.h"
#include "HomingMissile.h"
#include <windows.h>
#include "InteriorLevelInstance.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"



// Sets default values
ABaseSpaceship::ABaseSpaceship()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	SetRootComponent(ShipMesh);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(ShipMesh);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	PhysicsThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("PhysicsThrust"));
	PhysicsThruster->SetupAttachment(ShipMesh);
	ProjectileLaunchMuzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	ProjectileLaunchMuzzle->SetupAttachment(ShipMesh);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));
	ParticleSystemComp->SetupAttachment(ShipMesh);
	ParticleSystemComp->SetVisibility(false);

}

void ABaseSpaceship::AddFuel(float amount)
{
	CurrentFuel = FMath::Clamp(CurrentFuel + amount, 0, MaxFuel);
	onFuelChange.Broadcast(CurrentFuel, MaxFuel);
}

// Called when the game starts or when spawned
void ABaseSpaceship::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<ASpaceShipGameMode>(UGameplayStatics::GetGameMode(this));
	spaceController = Cast<ASEController>(GetOwner());
	spaceController->SetShip(this);
	//Instance = Cast<USEGameInstance>(GetGameInstance());
	//CurrentFuel = Instance->GetShipFuel();
	onFuelChange.Broadcast(CurrentFuel, MaxFuel);
	HealthComponent->OnDeath.AddDynamic(this, &ABaseSpaceship::OnDead);
	//SpawnInterior();
	
}

// Called every frame
void ABaseSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isCurrentlyAiming)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		APlayerCameraManager* PlayerCameraManager = PlayerController->PlayerCameraManager;
		FHitResult HitResult;
		FVector ViewLoc;
		FRotator ViewRot;
		PlayerCameraManager->GetCameraViewPoint(ViewLoc, ViewRot);
		FCollisionQueryParams CollisionParameters;
		FVector ViewpointDirection = ViewRot.Vector();
		FVector TraceEndLocation = ViewLoc + ViewpointDirection * 50000;
		CollisionParameters.AddIgnoredActor(this);
		FCollisionShape shape = FCollisionShape::MakeCapsule(FVector(100, 100, 100));
		if (GetWorld()->SweepSingleByChannel(HitResult, ViewLoc, TraceEndLocation, FQuat::Identity, ECC_GameTraceChannel2, shape, CollisionParameters))
		{
			

			if (!TargetedEnemies.Contains(HitResult.GetActor()))
			{
				//todo Find Widget on each one and activate it.
				TargetedEnemies.Add(HitResult.GetActor());

				for (AActor* target : TargetedEnemies)
				{
					if (UWidgetComponent* widget = target->FindComponentByClass<UWidgetComponent>())
					{
						widget->SetVisibility(true);
					}
				}
			}
		}
	}



}

void ABaseSpaceship::MaxSpeedBoost()
{
	if (!bCurrentlyBoosted)
	{
		MaxSpeed *= 2;
		Speed = MaxSpeed;
		bCurrentlyBoosted = true;
		OnBoost();
		GetWorldTimerManager().SetTimer(SpeedReturnTimer, this, &ABaseSpaceship::ReturnToNormalSpeed, BoostTime, false);

	}
	else
	{

		GetWorldTimerManager().ClearTimer(SpeedReturnTimer);
		GetWorldTimerManager().SetTimer(SpeedReturnTimer, this, &ABaseSpaceship::ReturnToNormalSpeed, BoostTime, false);

	}
	FMath::Clamp(CurrentFuel += 50, 0, MaxFuel);
	onFuelChange.Broadcast(CurrentFuel, MaxFuel);

}

// Called to bind functionality to input
void ABaseSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &ABaseSpaceship::ActivateShield);
	PlayerInputComponent->BindAction("Boost", IE_Released, this, &ABaseSpaceship::DeactivateShield);
	PlayerInputComponent->BindAction("Missiles", IE_Pressed, this, &ABaseSpaceship::AimMissiles);
	PlayerInputComponent->BindAction("Missiles", IE_Released, this, &ABaseSpaceship::ReleaseMissiles);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABaseSpaceship::Fire);
	PlayerInputComponent->BindAxis("MoveUp", this, &ABaseSpaceship::MoveUp);
	PlayerInputComponent->BindAxis("Thrust", this, &ABaseSpaceship::Thrust);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseSpaceship::MoveRight);
	PlayerInputComponent->BindAxis("Roll", this, &ABaseSpaceship::Roll);
	PlayerInputComponent->BindAxis("Elevate", this, &ABaseSpaceship::Elevate);
	PlayerInputComponent->BindAction("StopPiloting", IE_Pressed, this, &ABaseSpaceship::StopPiloting);



}

void ABaseSpaceship::SetShipInterior(AInteriorLevelInstance* shipInt)
{
	ShipInterior = shipInt;
}

void ABaseSpaceship::SetSpeed(float newSpeed)
{
	Speed = newSpeed;
}


void ABaseSpaceship::ActivateShield()
{
	ParticleSystemComp->SetVisibility(true);
	HealthComponent->SetCanTakeDamage(false);

}

void ABaseSpaceship::DeactivateShield()
{
	ParticleSystemComp->SetVisibility(false);
	HealthComponent->SetCanTakeDamage(true);


}

void ABaseSpaceship::AimMissiles()
{
	//TODO if missiles are available
	isCurrentlyAiming = true;

}

void ABaseSpaceship::ReleaseMissiles()
{
	isCurrentlyAiming = false;

	if (TargetedEnemies.Num() > 0)
	{
		//for the length of the array, spawn that many projectiles upon release.
		//each projectile is assigned the enemy of index as its homing target.

		for (int i = 0; i < TargetedEnemies.Num(); ++i)
		{
			if (TargetedEnemies[i])
			{
				FActorSpawnParameters params;
				params.Owner = this;
				params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				AHomingMissile* missile = GetWorld()->SpawnActor<AHomingMissile>(HomingMissileClass, ProjectileLaunchMuzzle->GetComponentTransform(), params);
				missile->SetHomingTarget(TargetedEnemies[i]);
			}
		}

		TargetedEnemies.Empty();
	}
}

void ABaseSpaceship::MoveUp(float Value)
{
	ChangeShipTorque(Value, PitchPower, ShipMesh->GetForwardVector());
}

void ABaseSpaceship::Elevate(float Value)
{
	float ElevatePower = ((Value * LiftPower) / GetActorUpVector().Z) * ShipMesh->GetMass();

	PhysicsThruster->ThrustStrength = ElevatePower;
}

void ABaseSpaceship::Thrust(float Value)
{
	if (CurrentFuel > 0)
	{
		//the +1 and /2 prevent the ship from going backwards, pressing "S" will only slow the ship to a halt.
		float alpha = (Value + 1) / 2;
		float buildUpSpeed = FMath::Lerp(0, MaxSpeed, alpha);
		float toMaxSpeed = FMath::FInterpTo(Speed, buildUpSpeed, GetWorld()->GetDeltaSeconds(), SpeedBuildUpRate);

		if (!FMath::IsNearlyEqual(Value, 0.0f, 0.1))
		{
			Speed = toMaxSpeed;
			ForwardVelocity = ShipMesh->GetRightVector() * -Speed;
			ShipMesh->AddForce(ForwardVelocity * 1000);
		}
		CurrentFuel = FMath::Clamp(CurrentFuel -= Value * 0.1, 0, MaxFuel);
		//Instance->SetShipFuel(CurrentFuel);
		onFuelChange.Broadcast(CurrentFuel, MaxFuel);
		
	}

}

void ABaseSpaceship::MoveRight(float Value)
{
	if (CurrentFuel > 0)
	{
		ChangeShipTorque(Value, TurnPower, ShipMesh->GetUpVector());
	}

}

void ABaseSpaceship::Roll(float Value)
{
	ChangeShipTorque(Value, RollingPower, ShipMesh->GetRightVector());

}

void ABaseSpaceship::SpawnInterior()
{
	ShipInterior = GetWorld()->SpawnActor<AInteriorLevelInstance>(ShipInteriorClass);
	ShipInterior->SetActorHiddenInGame(true);
}

void ABaseSpaceship::StopPiloting()
{
	//if (playerExplorer)
	//{
	//	spaceController->UnPossess();
	//	spaceController->Possess(playerExplorer);
	//}
}

void ABaseSpaceship::Fire()
{

	FVector WorldLocation;
	FVector WorldDirection;
	if (spaceController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FActorSpawnParameters params;
		params.Owner = this;
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileLaunchMuzzle->GetComponentTransform(), params);
		projectile->SetTarget(WorldDirection);
	}


}

void ABaseSpaceship::InteractWith(AExplorerCharacter* player)
{
	player->SetActorHiddenInGame(true);
	spaceController->bShowMouseCursor = true;
	spaceController->UnPossess();
	spaceController->Possess(this);
	//player->SetActorLocation(ShipInterior->GetPlayerStartLocation()->GetComponentLocation());
}

void ABaseSpaceship::ChangeShipTorque(float InputValue, float Power, FVector ShipVector)
{
	float torquePower = InputValue * Power;
	FVector torque = ShipVector * torquePower;
	ShipMesh->AddTorqueInDegrees(torque, NAME_None, true);
}

void ABaseSpaceship::ReturnToNormalSpeed()
{
	MaxSpeed /= 2;
	Speed = MaxSpeed;
	OnBoostDone();
	bCurrentlyBoosted = false;
}

