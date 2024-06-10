// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include "MyProjectCharacter.h"
#include "BulletCounter.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/WidgetComponent.h"
#include "TP_WeaponComponent.h"


void AMyProjectGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerHUDClass != nullptr)
	{
		BulletCounterComp = CreateWidget<UBulletCounter>(GetWorld(), PlayerHUDClass);
		//BulletCounterComp->Update();
		BulletCounterComp->AddToViewport();
		
		
	}



}

AMyProjectGameMode::AMyProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	



}
