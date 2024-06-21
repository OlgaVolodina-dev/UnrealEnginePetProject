// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableComponent.h"
#include "MyProjectCharacter.h"
#include "TP_WeaponComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"



// Sets default values for this component's properties
UThrowableComponent::UThrowableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);


	// ...
}

void UThrowableComponent::AttachThrowable(AMyProjectCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	

	if (Character == nullptr)
	{
		return;
	}
	if (ThrowMappingContext == nullptr || ThrowAction == nullptr)
	{
		return;
	}
	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(ThrowMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Completed, this, &UThrowableComponent::Throw);
			EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, this, &UThrowableComponent::PredictGrenadePath);
		}
	}
}


void UThrowableComponent::Throw()
{
	//if (Character || Character->GetGrenadesNumber() == 0)
	//{
	//	return;
	//}

	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = Character->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// Spawn the projectile at the muzzle
			World->SpawnActor<AMyProjectProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

	//Character->ToogleGrenadesNumber(-1);
	
}

void UThrowableComponent::PredictGrenadePath()
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
		FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		FVector SpawnLocation = Character->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
		
		FPredictProjectilePathParams params;
		FPredictProjectilePathResult res;
		
		params.ProjectileRadius = 10.0f;
		params.StartLocation = SpawnLocation;
		params.LaunchVelocity = SpawnRotation.RotateVector(FVector(400.0f, 0.0f, 0.0f));
		params.MaxSimTime = 1.0f;

		params.DrawDebugType = EDrawDebugTrace::Persistent;
		
		UGameplayStatics::Blueprint_PredictProjectilePath_Advanced(World, params, res);
	}
}

// Called when the game starts
void UThrowableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UThrowableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

