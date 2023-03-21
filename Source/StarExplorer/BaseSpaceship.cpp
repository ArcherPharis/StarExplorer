// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpaceship.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SEController.h"
#include "ExplorerCharacter.h"
#include "SpaceShipGameMode.h"
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

}

// Called when the game starts or when spawned
void ABaseSpaceship::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<ASpaceShipGameMode>(UGameplayStatics::GetGameMode(this));
	if (gameMode->GetSpacePlayer())
	{
		playerExplorer = gameMode->GetSpacePlayer();
		playerExplorer->SetExplorerShip(this);
		spaceController = Cast<ASEController>(playerExplorer->GetOwner());

	}
	SpawnInterior();
	
}

// Called every frame
void ABaseSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);




}

// Called to bind functionality to input
void ABaseSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &ABaseSpaceship::Boost);
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

}

void ABaseSpaceship::MoveRight(float Value)
{
	ChangeShipTorque(Value, TurnPower, ShipMesh->GetUpVector());

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
	if (playerExplorer)
	{
		spaceController->UnPossess();
		spaceController->Possess(playerExplorer);
	}
}

void ABaseSpaceship::InteractWith(AExplorerCharacter* player)
{
	//spaceController->UnPossess();
	//spaceController->Possess(this);
	player->SetActorLocation(ShipInterior->GetPlayerStartLocation()->GetComponentLocation());
}

void ABaseSpaceship::ChangeShipTorque(float InputValue, float Power, FVector ShipVector)
{
	float torquePower = InputValue * Power;
	FVector torque = ShipVector * torquePower;
	ShipMesh->AddTorqueInDegrees(torque, NAME_None, true);
}

