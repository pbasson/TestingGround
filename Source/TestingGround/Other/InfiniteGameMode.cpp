// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteGameMode.h"
#include "Navmesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteGameMode::AInfiniteGameMode()
{
	NavMeshBoundsVolumePool = CreateAbstractDefaultSubobject<UActorPool>(TEXT("NavMeshBoundsVolumePool"));
}

void AInfiniteGameMode::AddToPool(class ANavMeshBoundsVolume *VolumeToAdd) 
{
	NavMeshBoundsVolumePool->AddActor(VolumeToAdd);
}

void AInfiniteGameMode::PopulateBoundsVolumePool() 
{
	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}