// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplorerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "IInteractableInterface.h"
#include "Camera/CameraComponent.h"

// Sets default values
AExplorerCharacter::AExplorerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

}

// Called when the game starts or when spawned
void AExplorerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplorerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AExplorerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AExplorerCharacter::Interact);

}

void AExplorerCharacter::SetExplorerShip(ABaseSpaceship* myNewShip)
{
	MySpaceship = myNewShip;
}

void AExplorerCharacter::Interact()
{
	FHitResult traceResult;
	FVector ViewLoc;
	FRotator ViewRot;
	FCollisionQueryParams CollisionParameters;
	//CollisionParameters.AddIgnoredActor(this);
	GetActorEyesViewPoint(ViewLoc, ViewRot);
	if (GetWorld()->LineTraceSingleByChannel(traceResult, ViewLoc, ViewLoc + ViewRot.Vector() * GrabRange, ECC_GameTraceChannel1, CollisionParameters))
	{
		if (traceResult.bBlockingHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found something interactable"));
			AActor* hitActor = traceResult.GetActor();
			IIInteractableInterface* interactInferface = Cast<IIInteractableInterface>(hitActor);
			interactInferface->InteractWith(this);

		}
	}
}

