// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include "MyProjectCharacter.h"
#include "BulletCounter.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/WidgetComponent.h"
#include "TP_WeaponComponent.h"
#include "PauseMenu.h"


void AMyProjectGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerHUDClass != nullptr)
	{
		BulletCounterComp = CreateWidget<UBulletCounter>(GetWorld(), PlayerHUDClass);
		//BulletCounterComp->Update();
		BulletCounterComp->AddToViewport();
	}


	if (PauseMenuClass != nullptr)
	{
		PauseMenuWidget = CreateWidget<UPauseMenu>(GetWorld(), PauseMenuClass);
	}
}

AMyProjectGameMode::AMyProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	



}
