// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UHealthComponent::Initialize(int maxhealth, AActor* actor)
{
	CurrentHealth = MaxHealth = maxhealth;
	Owner = TWeakObjectPtr<AActor>(actor);

}

void UHealthComponent::ChangeHealth(int diff)
{
	CurrentHealth = FMath::Max(FMath::Min(CurrentHealth + diff, MaxHealth), 0);
	if (CurrentHealth == 0 && Owner != nullptr)
	{
		Owner->Destroy();
	}
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

