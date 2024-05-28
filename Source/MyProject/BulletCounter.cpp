// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletCounter.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UBulletCounter::Update()
{
	BulletCounterBar->SetPercent(100);
	CurrentBulletCount->SetText(FText::AsNumber(3));
	MaxBulletCount->SetText(FText::AsNumber(30));
}
