// Copyright Epic Games, Inc. All Rights Reserved.
#include "MyProjectCharacter.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MyProjectProjectile.h"
#include "Components/WidgetComponent.h"
#include "BulletCounter.h"
#include "TP_WeaponComponent.h"
#include "MyProjectGameMode.h"
#include "PauseMenu.h"
#include "Kismet/KismetMathLibrary.h"
#include "ThrowableComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AMyProjectCharacter



AMyProjectCharacter::AMyProjectCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));

	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	GrenadesNumber = 0;
	
	


	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	ThrowableComponent = CreateDefaultSubobject<UThrowableComponent>(TEXT("ThrowableComponent"));
	AddOwnedComponent(ThrowableComponent);
}



void AMyProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

//////////////////////////////////////////////////////////////////////////// Input

void AMyProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyProjectCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyProjectCharacter::Look);
		EnhancedInputComponent->BindAction(PauseMenuAction, ETriggerEvent::Started, this, &AMyProjectCharacter::OpenPauseMenu);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AMyProjectCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AMyProjectCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMyProjectCharacter::OpenPauseMenu(const FInputActionValue& Value)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{

		//if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		//{
		//	// Fire
		//	EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
		//}

		AMyProjectGameMode* GameMode = static_cast<AMyProjectGameMode*>(GetWorld()->GetAuthGameMode());
		if (GameMode && GameMode->PauseMenuWidget)
		{
			GameMode->PauseMenuWidget->OpenMenu(PlayerController);
		}
	}
}

void AMyProjectCharacter::SetHasRifle(bool bNewHasRifle, UTP_WeaponComponent* weaponComponent)
{
	bHasRifle = bNewHasRifle;
	PickedWeapon = weaponComponent;

	AMyProjectGameMode* GameMode = static_cast<AMyProjectGameMode*>(GetWorld()->GetAuthGameMode());
	PickedWeapon->OnAmmoChange.AddUniqueDynamic(GameMode->BulletCounterComp, &UBulletCounter::Update);
}

bool AMyProjectCharacter::GetHasRifle()
{
	return bHasRifle;
}

int AMyProjectCharacter::GetGrenadesNumber()
{
	return GrenadesNumber;
}

void AMyProjectCharacter::SetGrenadesNumber(int num)
{
	GrenadesNumber = FMath::Max(num, 0);
	if (GrenadesNumber != 0)
	{
		ThrowableComponent->AttachThrowable(this);
	}
}

void AMyProjectCharacter::ToogleGrenadesNumber(int diff)
{
	SetGrenadesNumber(GrenadesNumber + diff);

}
