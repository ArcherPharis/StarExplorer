// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpaceship.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SEController.h"
#include "ExplorerCharacter.h"
#include "SpaceShipGameMode.h"
#include "SEGameInstance.h"
#include "Projectile.h"
#include "InteriorLevelInstance.h"
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
	//SpawnInterior();
	
}

// Called every frame
void ABaseSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void ABaseSpaceship::MaxSpeedBoost()
{
	if (!bCurrentlyBoosted)
	{
		MaxSpeed *= 2;
		Speed = MaxSpeed;
		bCurrentlyBoosted = true;
		Camera->FieldOfView = 105.f;
		GetWorldTimerManager().SetTimer(SpeedReturnTimer, this, &ABaseSpaceship::ReturnToNormalSpeed, BoostTime, false);

	}

}

// Called to bind functionality to input
void ABaseSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &ABaseSpaceship::Boost);
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

void ABaseSpaceship::Boost()
{
	UE_LOG(LogTemp, Warning, TEXT("Boosted"));
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
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileLaunchMuzzle->GetComponentTransform());
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
	Camera->FieldOfView = 90.f;
	bCurrentlyBoosted = false;
}

