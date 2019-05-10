// Fill out your copyright notice in the Description page of Project Settings.

#include "GrassComponent.h"

// Sets default values for this component's properties
UGrassComponent::UGrassComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UGrassComponent::SpawnGrass()
{
	for (size_t i = 0; i < SpawnCount; i++)
	{
		FVector Location = FMath::RandPointInBox(SpawningExtents);
		AddInstance(FTransform(Location));
	}
}

// Called when the game starts
void UGrassComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnGrass();
	
}


// Called every frame
void UGrassComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

