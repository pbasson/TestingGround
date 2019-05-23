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
	AInfiniteGameMode();
	UFUNCTION(BlueprintCallable, Category = "Bounds")
	void PopulateBoundsVolumePool();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
	class UActorPool* NavMeshBoundsVolumePool;

private:
	void AddToPool(class ANavMeshBoundsVolume* VolumeToAdd);

};
