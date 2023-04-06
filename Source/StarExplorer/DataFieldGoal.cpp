// Fill out your copyright notice in the Description page of Project Settings.


#include "DataFieldGoal.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MissionGamemode.h"
#include "DataFieldWidget.h"

// Sets default values
ADataFieldGoal::ADataFieldGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject< USceneComponent>(TEXT("RootComp"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	HitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("HitSphere"));
	HitSphere->SetupAttachment(Mesh);
	HitSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

// Called when the game starts or when spawned
void ADataFieldGoal::BeginPlay()
{
	Super::BeginPlay();
	HitSphere->OnComponentBeginOverlap.AddDynamic(this, &ADataFieldGoal::AttemptCapture);
	HitSphere->OnComponentEndOverlap.AddDynamic(this, &ADataFieldGoal::LeaveCaptureRange);

	
}

// Called every frame
void ADataFieldGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bCurrentlyCapturing)
	{
		if (DataFieldWidget)
		{
			FMath::Clamp(CurrentCapture += ProgressClimbAmount, 0, MaxCaptureAmount);
			DataFieldWidget->UpdateProgressBar(CurrentCapture, MaxCaptureAmount);
		}
	}

}

void ADataFieldGoal::CaptureComplete()
{

	if (DataFieldWidget)
	{
		DataFieldWidget->RemoveFromParent();
	}
	AMissionGamemode* GM = Cast<AMissionGamemode>(UGameplayStatics::GetGameMode(this));
	GM->GoalRingPassed(this);

}

void ADataFieldGoal::AttemptCapture(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (APlayerController* cont = Cast<APlayerController>(OtherActor->GetOwner()))
	{
		DataFieldWidget = CreateWidget<UDataFieldWidget>(cont, DataFieldWidgetClass);
		DataFieldWidget->AddToViewport();
		bCurrentlyCapturing = true;
		DataFieldWidget->OnPercentageComplete.AddDynamic(this, &ADataFieldGoal::CaptureComplete);
	}
	
}

void ADataFieldGoal::LeaveCaptureRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (DataFieldWidget)
	{
		bCurrentlyCapturing = false;
		CurrentCapture = 0;
		DataFieldWidget->UpdateProgressBar(CurrentCapture, MaxCaptureAmount);
		DataFieldWidget->RemoveFromParent();
	}
}

