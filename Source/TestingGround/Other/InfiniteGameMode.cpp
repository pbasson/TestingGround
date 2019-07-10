// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteGameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"
#include "WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Terrain/Tile.h"

AInfiniteGameMode::AInfiniteGameMode()
{
	NavMeshBoundsVolumePool = CreateAbstractDefaultSubobject<UActorPool>(TEXT("NavMeshBoundsVolumePool"));
	ScoreValue = 0;
}

void AInfiniteGameMode::AddToPool(class ANavMeshBoundsVolume *VolumeToAdd) 
{
	NavMeshBoundsVolumePool->AddActor(VolumeToAdd);
}


void AInfiniteGameMode::BeginPlay()
{
	Super::BeginPlay();

	PopulateBoundsVolumePool();
	for (int i = 0; i < 4; i++)
	{ SpawnActor(); }

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

void AInfiniteGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{ CurrentWidget->AddToViewport(); }
	}
}

void AInfiniteGameMode::CheckMenu()
{
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{ GamePaused = true; }
}

void AInfiniteGameMode::SpawnActor()
{
	ATile* SpawnedTile = GetWorld()->SpawnActor<ATile>(Tile_BP->GetAuthoritativeClass(), NextTilePos);
	SpawnedTile->SetPool(NavMeshBoundsVolumePool);
	NextTilePos = SpawnedTile->GetAttachment();
}
