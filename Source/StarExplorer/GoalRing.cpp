// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalRing.h"
#include "Components/SphereComponent.h"
#include "BaseSpaceship.h"
#include "MissionGamemode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoalRing::AGoalRing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RingMesh"));
	SetRootComponent(RingMesh);
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	TriggerSphere->SetupAttachment(RingMesh);
	TriggerSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

// Called when the game starts or when spawned
void AGoalRing::BeginPlay()
{
	Super::BeginPlay();
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AGoalRing::OnShipEnter);
}

// Called every frame
void AGoalRing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoalRing::OnShipEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseSpaceship* Ship = Cast<ABaseSpaceship>(OtherActor);
	MissionGamemode = Cast<AMissionGamemode>(UGameplayStatics::GetGameMode(this));

	if (Ship)
	{
		Ship->MaxSpeedBoost();
		MissionGamemode->GoalRingPassed(this);
		Destroy();
	}
}

