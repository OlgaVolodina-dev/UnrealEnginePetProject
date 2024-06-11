// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "PauseMenu.h"

void UPauseMenu::OpenMenu(APlayerController* playerInputComponent)
{
	PlayerInputComponent = playerInputComponent;
	if (!WasGamePaused)
	{

		AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		PlayerInputComponent->bShowMouseCursor = true;
		//UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(mPlayerController);
		WasGamePaused = true;
	}
}

void UPauseMenu::CloseMenu()
{
	if (WasGamePaused)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		RemoveFromParent();
		WasGamePaused = false;

		PlayerInputComponent->bShowMouseCursor = false;
		//UWidgetBlueprintLibrary::SetInputMode_GameOnly(mPlayerController);
	}
}
