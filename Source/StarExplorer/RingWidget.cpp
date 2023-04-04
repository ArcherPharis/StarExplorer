// Fill out your copyright notice in the Description page of Project Settings.


#include "RingWidget.h"
#include "Components/TextBlock.h"

void URingWidget::SetRingsRemainingText(int amount)
{
	RingsRemainingText->SetText(FText::FromString(FString::FromInt(amount)));
}

void URingWidget::SetTotalRingsText(int amount)
{
	RingsTotalText->SetText(FText::FromString(FString::FromInt(amount)));

}
