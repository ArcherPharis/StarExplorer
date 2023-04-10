// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UHealthComponent::SetCanTakeDamage(bool CanTakeDamage)
{
	bAcceptDamage = CanTakeDamage;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if (bAcceptDamage)
	{
		Health = FMath::Clamp(Health - Damage, 0, MaxHealth);
		OnHealthChange.Broadcast(Health, MaxHealth);

		if (Health == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Dead!"));
			OnDeath.Broadcast();
		}

		DamageCauser->Destroy();
	}
}

