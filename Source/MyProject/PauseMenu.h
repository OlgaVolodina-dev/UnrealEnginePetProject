// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */

class UButton;

UCLASS()
class MYPROJECT_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void OpenMenu(APlayerController* PlayerInputComponent);

	UFUNCTION(BlueprintCallable)
	void CloseMenu();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;


private:
	APlayerController* PlayerInputComponent;

	bool WasGamePaused = false;
};
