// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BulletCounter.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MYPROJECT_API UBulletCounter : public UUserWidget
{
	GENERATED_BODY()
public:

	void Update();

protected:
	UPROPERTY( meta = (BindWidget))
	class UProgressBar* BulletCounterBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentBulletCount;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxBulletCount;

};
