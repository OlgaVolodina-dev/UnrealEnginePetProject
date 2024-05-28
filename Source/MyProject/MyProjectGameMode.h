// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProjectGameMode.generated.h"


UCLASS(minimalapi)
class AMyProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;


public:
	AMyProjectGameMode();

	// All on screen widgets to add to the HUD on BeginPlay
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	UPROPERTY(EditAnywhere)
	class UBulletCounter* BulletCounterComp;
};



