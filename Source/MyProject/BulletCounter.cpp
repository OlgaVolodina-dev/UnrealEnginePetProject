// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletCounter.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"




void UBulletCounter::Update(int currentBulletCount, int maxBulletCount)
{
	BulletCounterBar->SetPercent(currentBulletCount/ float(maxBulletCount));
	CurrentBulletCount->SetText(FText::AsNumber(currentBulletCount));
	MaxBulletCount->SetText(FText::AsNumber(maxBulletCount));
}
