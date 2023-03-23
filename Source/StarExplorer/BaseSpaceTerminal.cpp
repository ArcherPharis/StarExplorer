// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpaceTerminal.h"

// Sets default values
ABaseSpaceTerminal::ABaseSpaceTerminal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(meshComponent);
	meshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);

}

// Called when the game starts or when spawned
void ABaseSpaceTerminal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseSpaceTerminal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseSpaceTerminal::InteractWith(AExplorerCharacter* player)
{
	UE_LOG(LogTemp, Warning, TEXT("Interacted With"));
}

