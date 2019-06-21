// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteGameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteGameMode::AInfiniteGameMode()
{
	NavMeshBoundsVolumePool = CreateAbstractDefaultSubobject<UActorPool>(TEXT("NavMeshBoundsVolumePool"));
	ScoreValue = 0;
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

FString AInfiniteGameMode::GetScoreValue()
{
	return "Score: " + FString::FromInt(ScoreValue);
}

int AInfiniteGameMode::SetScoreValue()
{
	return ++ScoreValue;
}
