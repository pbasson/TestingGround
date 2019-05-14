// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Other/TGGameMode.h"
#include "InfiniteGameMode.generated.h"

class ANavMeshBoundsVolume;

UCLASS()
class TESTINGGROUND_API AInfiniteGameMode : public ATGGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Bounds")
	void PopulateBoundsVolumePool();

private:
	void AddToPool(class ANavMeshBoundsVolume* VolumeToAdd);
};
