// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionPlanet.h"
#include "BaseSpaceship.h"
#include "SEController.h"
#include "Kismet/GameplayStatics.h"
#include "BeginMissionWidget.h"
#include "Components/SphereComponent.h"

// Sets default values
AMissionPlanet::AMissionPlanet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(MeshComp);
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComponent->SetupAttachment(MeshComp);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

// Called when the game starts or when spawned
void AMissionPlanet::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AMissionPlanet::QueryMissionStart);
}

// Called every frame
void AMissionPlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMissionPlanet::QueryMissionStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ship = Cast<ABaseSpaceship>(OtherActor);

	if (!MissionWidget)
	{
		MissionWidget = CreateWidget<UBeginMissionWidget>(GetWorld(), MissionWidgetClass);
		MissionWidget->onConfirm.AddDynamic(this, &AMissionPlanet::BeginMission);
		MissionWidget->onCancel.AddDynamic(this, &AMissionPlanet::CancelQuery);

	}

	if (ship)
	{
		cont = ship->GetSpaceController();
		OtherActor->DisableInput(cont);
		cont->SetInputMode(FInputModeUIOnly());
		MissionWidget->AddToViewport();
		cont->bShowMouseCursor = true;
		ship->SetSpeed(0);
	}
}

void AMissionPlanet::BeginMission()
{
	ship->EnableInput(cont);
	cont->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, PlanetLevel);
}

void AMissionPlanet::CancelQuery()
{
	if (MissionWidget)
	{
		MissionWidget->RemoveFromViewport();
		ship->EnableInput(cont);
		cont->SetInputMode(FInputModeGameOnly());
	}
}

