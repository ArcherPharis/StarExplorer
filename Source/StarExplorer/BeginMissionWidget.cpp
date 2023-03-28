// Fill out your copyright notice in the Description page of Project Settings.


#include "BeginMissionWidget.h"
#include "Components/Button.h"

void UBeginMissionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BeginMissionButton->OnClicked.AddDynamic(this, &UBeginMissionWidget::StartMission);
	CancelButton->OnClicked.AddDynamic(this, &UBeginMissionWidget::Cancel);

}

void UBeginMissionWidget::StartMission()
{
	onConfirm.Broadcast();
}

void UBeginMissionWidget::Cancel()
{
	onCancel.Broadcast();
}
