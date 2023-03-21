// Fill out your copyright notice in the Description page of Project Settings.


#include "InteriorLevelInstance.h"

AInteriorLevelInstance::AInteriorLevelInstance()
{
	PlayerStartLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Start Location"));
	PlayerStartLocation->SetupAttachment(RootComponent);
}
